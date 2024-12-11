/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 05:09 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "funciones.h"
using namespace std;

#define MAX_ESCALAS 5
#define MAX_COD_CUR 8
#define MAX_NOM_CUR 60
#define MAX_NOM_DOC 40
#define MAX_NOM_ALU 40
#define MAX_MODAL 16
#define MAX_LIN_PRUEBA 150
#define MAX_LIN_FINAL 80
#define NO_ENCONTRADO -1

void inicializarArchivos() {
    ofstream archAlumnos = abrirArchSalida("Alumnos.bin", true);
    ofstream archEscalas = abrirArchSalida("Escalas.bin", true);
    double escala = 0;
    // Inicializar archivo de escalas
    for (int i = 0; i < MAX_ESCALAS; i++) 
        archEscalas.write(reinterpret_cast<char*>(&escala), sizeof(double));
}

void procesarAlumnosxCursos() {
    ifstream archTxt    = abrirArchEntrada("AlumnosxCursos.txt", false);
    ofstream archCursos = abrirArchSalida("Cursos.bin", true);
    fstream archAlumnos = abrirArchBinEntSal("Alumnos.bin");
    ofstream archClases = abrirArchSalida("ListaDeClases.bin", true);
    char codCur[MAX_COD_CUR]{}, nomCur[MAX_NOM_CUR]{}, nomDoc[MAX_NOM_DOC]{},
            nomAlu[MAX_NOM_ALU]{}, modalidad, car;
    int semestre, codDoc, codAlu, porcVirt, escala, cantAlu = 0;
    double credCur;
    bool primeraVez = true;
    // Leer línea por línea
    while (true) {
        archTxt >> semestre;
        if (archTxt.eof()) break;
        if (archTxt.fail()) {
            archTxt.clear();
            // Agregar el curso anterior
            if (primeraVez) primeraVez = false;
            else agregarCurso(archCursos, codCur, nomCur, credCur, codDoc,
                    nomDoc, cantAlu);
            // Leer datos del curso
            archTxt >> codCur >> nomCur >> credCur >> codDoc >> nomDoc;
        } else {
            // Inicializar datos del alumno
            modalidad = 'P';
            porcVirt = 0;
            cantAlu++;
            // Leer datos del alumno
            archTxt >> car >> codAlu >> nomAlu >> escala;
            if (archTxt.fail()) {
                archTxt.clear();
                archTxt >> modalidad;
                if (modalidad == 'S') archTxt >> porcVirt;
                archTxt >> escala;
            }
            // Agregar datos a los archivos binarios
            procesarAlumno(archAlumnos, semestre, codAlu, nomAlu, modalidad,
                    porcVirt, escala, credCur);
            agregarClase(archClases, codCur, semestre, codAlu);
        }
    }
    // Agregar el último curso
    agregarCurso(archCursos, codCur, nomCur, credCur, codDoc, nomDoc, cantAlu);
}

void agregarCurso(ofstream &arch, char *codCur, char *nomCur, double credCur,
        int codDoc, char *nomDoc, int &cantAlu) {
    double total = 0;
    // Inicializar los datos
    formatearNombre(nomCur);
    formatearNombre(nomDoc);
    // Guardar el curso en el archivo binario
    arch.write(reinterpret_cast<const char *>(codCur), sizeof(char)*MAX_COD_CUR);
    arch.write(reinterpret_cast<const char *>(nomCur), sizeof(char)*MAX_NOM_CUR);
    arch.write(reinterpret_cast<const char *>(&credCur), sizeof(double));
    arch.write(reinterpret_cast<const char *>(&codDoc), sizeof(int));
    arch.write(reinterpret_cast<const char *>(nomDoc), sizeof(char)*MAX_NOM_DOC);
    arch.write(reinterpret_cast<const char *>(&cantAlu), sizeof(int));
    arch.write(reinterpret_cast<const char *>(&total), sizeof(double));
    // Reiniciar el contador
    cantAlu = 0;
}

void procesarAlumno(fstream &arch, int semestre, int codAlu, char *nomAlu,
        char modalidad, int porcVirt, int escala, double credCur) {
    int tamReg = sizeof(char)*(MAX_NOM_ALU+MAX_MODAL) + sizeof(int)*3 + sizeof(double)*3;
    char modalTexto[MAX_MODAL]{};
    double porcDouble = porcVirt / 100.0, costo = 0, totalCred;
    // Calcular tamaño de registro y número de registros
    int posAlu = buscarAlumno(arch, tamReg, semestre, codAlu);
    if (posAlu != NO_ENCONTRADO) {
        // Actualizar créditos
        arch.seekg(tamReg*(posAlu+1) - sizeof(double)*2, ios::beg);
        arch.read(reinterpret_cast<char *>(&totalCred), sizeof(double));
        totalCred += credCur;
        arch.seekg(tamReg*(posAlu+1) - sizeof(double)*2, ios::beg);
        arch.write(reinterpret_cast<const char *>(&totalCred), sizeof(double));
    } else {
        // Inicializar los datos
        if (modalidad == 'P') strcpy(modalTexto, "PRESENCIAL");
        else if (modalidad == 'V') strcpy(modalTexto, "VIRTUAL");
        else strcpy(modalTexto, "SEMIPRESENCIAL");
        formatearNombre(nomAlu);
        // Guardar datos en el archivo binario
        arch.seekg(0, ios::end);
        arch.write(reinterpret_cast<const char *>(&semestre), sizeof(int));
        arch.write(reinterpret_cast<const char *>(&codAlu), sizeof(int));
        arch.write(reinterpret_cast<const char *>(nomAlu), sizeof(char)*MAX_NOM_ALU);
        arch.write(reinterpret_cast<const char *>(modalTexto), sizeof(char)*MAX_MODAL);
        arch.write(reinterpret_cast<const char *>(&porcDouble), sizeof(double));
        arch.write(reinterpret_cast<const char *>(&escala), sizeof(int));
        arch.write(reinterpret_cast<const char *>(&credCur), sizeof(double));
        arch.write(reinterpret_cast<const char *>(&costo), sizeof(double));
    }
}

int buscarAlumno(fstream &arch, int tamReg, int semBuscado, int codBuscado) {
    int numReg = obtenerNumReg(arch, tamReg), semLeido, codLeido;
    for (int pos = 0; pos < numReg; pos++) {
        arch.seekg(pos*tamReg, ios::beg);
        arch.read(reinterpret_cast<char *>(&semLeido), sizeof(int));
        arch.read(reinterpret_cast<char *>(&codLeido), sizeof(int));
        if (semBuscado == semLeido && codBuscado == codLeido) return pos;
    }
    return NO_ENCONTRADO;
}

void agregarClase(ofstream &arch, char *codCur, int semestre, int codAlu) {
    arch.write(reinterpret_cast<const char *>(codCur), sizeof(char)*MAX_COD_CUR);
    arch.write(reinterpret_cast<const char *>(&semestre), sizeof(int));
    arch.write(reinterpret_cast<const char *>(&codAlu), sizeof(int));
}

void procesarEscalas() {
    ifstream archTxt = abrirArchEntrada("Escalas.txt", false);
    fstream archBin = abrirArchBinEntSal("Escalas.bin");
    double escala;
    char car;
    int indice;
    // Leer línea por línea
    while (true) {
        archTxt >> car;
        if (archTxt.eof()) break;
        archTxt >> indice >> escala;
        // Guardar escala en el lugar correspondiente
        archBin.seekg(sizeof(double) * (indice - 1), ios::beg);
        archBin.write(reinterpret_cast<char*>(&escala), sizeof(double));
    }
}

void imprimirReporteVerificacion(const char *nomArch) {
    ofstream archReporte = abrirArchSalida(nomArch, false);
    imprimirCursos(archReporte);
    imprimirAlumnos(archReporte);
    imprimirClases(archReporte);
    imprimirEscalas(archReporte);
}

void imprimirCursos(ofstream &archReporte) {
    ifstream archCursos  = abrirArchEntrada("Cursos.bin", true);
    char codCur[MAX_COD_CUR]{}, nomCur[MAX_NOM_CUR]{}, nomDoc[MAX_NOM_DOC]{};
    int codDoc, cantAlu;
    double credCur, ingresos;
    // Imprimir cabecera
    archReporte << fixed << setprecision(2);
    archReporte << "LISTADO DE CURSOS" << endl;
    imprimirLinea(archReporte, '-', MAX_LIN_PRUEBA);
    archReporte << left << setw(MAX_COD_CUR) << "Codigo" << setw(MAX_NOM_CUR)
            << "Nombre" << setw(10) << "Creditos" << setw(10) << "Docente"
            << setw(MAX_NOM_DOC) << "Nombre Docente" << setw(10) << "Num. Alu"
            << "Ingresos" << endl;
    // Leer línea por línea
    while (true) {
        archCursos.read(reinterpret_cast<char *>(codCur), sizeof(char)*MAX_COD_CUR);
        if (archCursos.eof()) break;
        archCursos.read(reinterpret_cast<char *>(nomCur), sizeof(char)*MAX_NOM_CUR);
        archCursos.read(reinterpret_cast<char *>(&credCur), sizeof(double));
        archCursos.read(reinterpret_cast<char *>(&codDoc), sizeof(int));
        archCursos.read(reinterpret_cast<char *>(nomDoc), sizeof(char)*MAX_NOM_DOC);
        archCursos.read(reinterpret_cast<char *>(&cantAlu), sizeof(int));
        archCursos.read(reinterpret_cast<char *>(&ingresos), sizeof(double));
        // Imprimir datos del curso
        archReporte << left << setw(MAX_COD_CUR) << codCur << setw(MAX_NOM_CUR)
                << nomCur << right << setw(8) << credCur << setw(2) << ' '
                << left << setw(10) << codDoc << setw(MAX_NOM_DOC) << nomDoc
                << right << setw(8) << cantAlu << setw(10) << ingresos << endl;
    }
    imprimirLinea(archReporte, '=', MAX_LIN_PRUEBA);
}

void imprimirAlumnos(ofstream &archReporte) {
    ifstream archAlumnos = abrirArchEntrada("Alumnos.bin", true);
    char nomAlu[MAX_NOM_ALU]{}, modalidad[MAX_MODAL];
    int semestre, codAlu, escala;
    double porcVirt, totalCred, costo;
    // Imprimir cabecera
    archReporte << "LISTADO DE ALUMNOS" << endl;
    imprimirLinea(archReporte, '-', MAX_LIN_PRUEBA);
    archReporte << left << setw(10) << "Semestre" << setw(8) << "Codigo"
            << setw(MAX_NOM_ALU) << "Nombre" << setw(MAX_MODAL) << "Modalidad"
            << setw(8) << "% Virt" << setw(8) << "Escala" << setw(10)
            << "Creditos" << "Costo sem." << endl;
    // Leer línea por línea
    while (true) {
        archAlumnos.read(reinterpret_cast<char *>(&semestre), sizeof(int));
        if (archAlumnos.eof()) break;
        archAlumnos.read(reinterpret_cast<char *>(&codAlu), sizeof(int));
        archAlumnos.read(reinterpret_cast<char *>(nomAlu), sizeof(char)*MAX_NOM_ALU);
        archAlumnos.read(reinterpret_cast<char *>(modalidad), sizeof(char)*MAX_MODAL);
        archAlumnos.read(reinterpret_cast<char *>(&porcVirt), sizeof(double));
        archAlumnos.read(reinterpret_cast<char *>(&escala), sizeof(int));
        archAlumnos.read(reinterpret_cast<char *>(&totalCred), sizeof(double));
        archAlumnos.read(reinterpret_cast<char *>(&costo), sizeof(double));
        // Imprimir datos del alumno
        archReporte << left << setw(10) << semestre << setw(8) << codAlu
                << setw(MAX_NOM_ALU) << nomAlu << setw(MAX_MODAL) << modalidad
                << right << setw(6) << porcVirt << setw(8) << escala << setw(10)
                << totalCred << setw(12) << costo << endl;
    }
    imprimirLinea(archReporte, '=', MAX_LIN_PRUEBA);
}

void imprimirClases(ofstream &archReporte) {
    ifstream archClases  = abrirArchEntrada("ListaDeClases.bin", true);
    char codCur[MAX_COD_CUR]{};
    int semestre, codAlu;
    // Imprimir cabecera
    archReporte << "LISTADO DE CLASES" << endl;
    imprimirLinea(archReporte, '-', MAX_LIN_PRUEBA);
    archReporte << left << setw(MAX_COD_CUR) << "Curso" << setw(10)
            << "Semestre" << "Alumno" << endl;
    // Leer línea por línea
    while (true) {
        archClases.read(reinterpret_cast<char *>(codCur), sizeof(char)*MAX_COD_CUR);
        if (archClases.eof()) break;
        archClases.read(reinterpret_cast<char *>(&semestre), sizeof(int));
        archClases.read(reinterpret_cast<char *>(&codAlu), sizeof(int));
        // Imprimir datos de las clases
        archReporte << setw(MAX_COD_CUR) << codCur << setw(10) << semestre
                << codAlu << endl;
    }
    imprimirLinea(archReporte, '=', MAX_LIN_PRUEBA);
}

void imprimirEscalas(ofstream &archReporte) {
    ifstream archEscalas = abrirArchEntrada("Escalas.bin", true);
    double escala;
    // Imprimir cabecera
    archReporte << "LISTADO DE ESCALAS" << endl;
    imprimirLinea(archReporte, '-', MAX_LIN_PRUEBA);
    archReporte << "Monto" << endl;
    // Leer línea por línea
    while (true) {
        archEscalas.read(reinterpret_cast<char *>(&escala), sizeof(double));
        if (archEscalas.eof()) break;
        archReporte << escala << endl;
    }
}

void actualizarAlumnosCursos() {
    fstream archCursos = abrirArchBinEntSal("Cursos.bin");
    fstream archAlumnos = abrirArchBinEntSal("Alumnos.bin");
    ifstream archClases = abrirArchEntrada("ListaDeClases.bin", true);
    ifstream archEscalas = abrirArchEntrada("Escalas.bin", true);
    int semestre, codAlu, posCur, posAlu, tamRegCur, tamRegAlu;
    char codCur[MAX_COD_CUR]{};
    // Calcular tamaños de registros
    tamRegCur = sizeof(char)*(MAX_COD_CUR+MAX_NOM_CUR+MAX_NOM_DOC) + sizeof(int)*2 + sizeof(double)*2;
    tamRegAlu = sizeof(char)*(MAX_NOM_ALU+MAX_MODAL) + sizeof(int)*3 + sizeof(double)*3;
    // Leer línea por línea
    while (true) {
        archClases.read(reinterpret_cast<char *>(codCur), sizeof(char)*MAX_COD_CUR);
        if (archClases.eof()) break;
        archClases.read(reinterpret_cast<char *>(&semestre), sizeof(int));
        archClases.read(reinterpret_cast<char *>(&codAlu), sizeof(int));
        // Buscar curso y alumno
        posCur = buscarCurso(archCursos, tamRegCur, codCur);
        posAlu = buscarAlumno(archAlumnos, tamRegAlu, semestre, codAlu);
        if (posCur != NO_ENCONTRADO && posAlu != NO_ENCONTRADO) {
            procesarClase(archCursos, archAlumnos, archEscalas, tamRegCur,
                    posCur, tamRegAlu, posAlu);
        }
    }
}

int buscarCurso(fstream &arch, int tamReg, const char *codBuscado) {
    char codLeido[MAX_COD_CUR]{};
    int numReg = obtenerNumReg(arch, tamReg);
    for (int pos = 0; pos < numReg; pos++) {
        arch.seekg(pos*tamReg, ios::beg);
        arch.read(reinterpret_cast<char *>(codLeido), sizeof(char)*MAX_COD_CUR);
        if (strcmp(codBuscado, codLeido) == 0) return pos;
    }
    return NO_ENCONTRADO;
}

void procesarClase(fstream &archCursos, fstream &archAlumnos, ifstream &archEscalas,
        int tamRegCur, int posCur, int tamRegAlu, int posAlu) {
    double credCur, ingresos, costoSem, montoEscala;
    int escala;
    // Obtener datos del curso
    archCursos.seekg(tamRegCur*posCur + sizeof(char)*(MAX_COD_CUR+MAX_NOM_CUR), ios::beg);
    archCursos.read(reinterpret_cast<char *>(&credCur), sizeof(double));
    archCursos.seekg(tamRegCur*(posCur+1) - sizeof(double), ios::beg);
    archCursos.read(reinterpret_cast<char *>(&ingresos), sizeof(double));
    // Obtener datos del alumno
    archAlumnos.seekg(tamRegAlu*(posAlu+1) - sizeof(double)*2 - sizeof(int), ios::beg);
    archAlumnos.read(reinterpret_cast<char *>(&escala), sizeof(int));
    archAlumnos.seekg(tamRegAlu*(posAlu+1) - sizeof(double), ios::beg);
    archAlumnos.read(reinterpret_cast<char *>(&costoSem), sizeof(double));
    // Obtener datos de la escala
    archEscalas.seekg(sizeof(double)*(escala-1), ios::beg);
    archEscalas.read(reinterpret_cast<char *>(&montoEscala), sizeof(double));
    // Actualizar datos
    ingresos += montoEscala * credCur;
    costoSem += montoEscala * credCur;
    // Colocar datos en los archivos binarios
    archCursos.seekg(tamRegCur*(posCur+1) - sizeof(double), ios::beg);
    archCursos.write(reinterpret_cast<const char *>(&ingresos), sizeof(double));
    archAlumnos.seekg(tamRegAlu*(posAlu+1) - sizeof(double), ios::beg);
    archAlumnos.write(reinterpret_cast<const char *>(&costoSem), sizeof(double));
}

void imprimirReporteFinal() {
    ifstream archCursos = abrirArchEntrada("Cursos.bin", true);
    ofstream archReporte = abrirArchSalida("ReporteFinal.txt", false);
    char codCur[MAX_COD_CUR]{}, nomCur[MAX_NOM_CUR]{}, nomDoc[MAX_NOM_DOC]{};
    int codDoc, cont = 1;
    double credCur;
    // Imprimir cabecera del reporte
    archReporte << fixed << setprecision(2);
    archReporte << "ENTIDAD EDUCATIVA LP1" << endl;
    archReporte << "LISTADOS DE CLASE" << endl;
    imprimirLinea(archReporte, '=', MAX_LIN_FINAL);
    // Leer línea por línea
    while (true) {
        archCursos.read(reinterpret_cast<char *>(codCur), sizeof(char)*MAX_COD_CUR);
        if (archCursos.eof()) break;
        archCursos.read(reinterpret_cast<char *>(nomCur), sizeof(char)*MAX_NOM_CUR);
        archCursos.read(reinterpret_cast<char *>(&credCur), sizeof(double));
        archCursos.read(reinterpret_cast<char *>(&codDoc), sizeof(int));
        archCursos.read(reinterpret_cast<char *>(nomDoc), sizeof(char)*MAX_NOM_DOC);
        archCursos.seekg(sizeof(int) + sizeof(double), ios::cur);
        // Imprimir datos del curso
        archReporte << right << setfill('0') << setw(2) << cont << setfill(' ')
                << left << setw(12) << ") Curso: " << nomCur << " ["
                << codCur << ']' << endl;
        archReporte << setw(4) << ' ' << "Profesor: " << nomDoc
                << " (" << codDoc << ')' << endl;
        archReporte << setw(4) << ' ' << "Creditos: " << credCur << endl;
        imprimirLinea(archReporte, '-', MAX_LIN_FINAL);
        archReporte << "CODIGO Y SEMESTRE DE ALUMNOS MATRICULADOS" << endl;
        imprimirLinea(archReporte, '-', MAX_LIN_FINAL);
        imprimirAlumnosEnCurso(archReporte, codCur);
        cont++;
    }
}

void imprimirAlumnosEnCurso(ofstream &archReporte, const char *codBuscado) {
    ifstream archClases = abrirArchEntrada("ListaDeClases.bin", true);
    int tamReg, numReg, semestre, anio, periodo, codAlu, cont = 1;
    char codLeido[MAX_COD_CUR]{};
    // Calcular tamaños y número de registros
    tamReg = sizeof(char)*MAX_COD_CUR + sizeof(int)*2;
    numReg = obtenerNumReg(archClases, tamReg);
    // Leer línea por línea
    while (true) {
        archClases.read(reinterpret_cast<char *>(codLeido), sizeof(char)*MAX_COD_CUR);
        if (archClases.eof()) break;
        archClases.read(reinterpret_cast<char *>(&semestre), sizeof(int));
        archClases.read(reinterpret_cast<char *>(&codAlu), sizeof(int));
        if (strcmp(codBuscado, codLeido) == 0) {
            // Calcular año y periodo del semestre
            anio = semestre / 10;
            periodo = semestre % 10;
            // Imprimir datos del alumno
            archReporte << right << setw(4) << ' ' << setfill('0') << setw(2)
                    << cont << setfill(' ') << ')' << setw(6) << codAlu
                    << setw(6) << anio << '-' << periodo << endl;
            cont++;
        }
    }
    imprimirLinea(archReporte, '=', MAX_LIN_FINAL);
}

/* Funciones auxiliares */

ifstream abrirArchEntrada(const char *nomArch, bool binario) {
    ifstream arch(nomArch, binario ? ios::in | ios::binary : ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchSalida(const char *nomArch, bool binario) {
    ofstream arch(nomArch, binario ? ios::out | ios::binary : ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

fstream abrirArchBinEntSal(const char *nomArch) {
    fstream arch(nomArch, ios::in | ios::out | ios::binary);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

int obtenerNumReg(istream &arch, int tamReg) {
    arch.seekg(0, ios::end);
    int tamArch = arch.tellg();
    arch.seekg(0, ios::beg);
    return tamArch / tamReg;
}

void imprimirLinea(ofstream &arch, char car, int cant) {
    for (int i = 0; i < cant; i++) arch.put(car);
    arch << endl;
}

void formatearNombre(char *nombre) {
    bool primerCaracter = true;
    for (int i = 0; nombre[i]; i++) {
        if (nombre[i] == '_' || nombre[i] == '/' || nombre[i] == '-') {
            nombre[i] = ' ';
            primerCaracter = true;
        } else if (primerCaracter) {
            primerCaracter = false;
        } else if (nombre[i] >= 'A' && nombre[i] <= 'Z') {
            nombre[i] = nombre[i] + 'a' - 'A';
        }
    }
}
