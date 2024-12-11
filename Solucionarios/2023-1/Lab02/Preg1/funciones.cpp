/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 12:22 AM
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
#define MAX_LIN_REP 150
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
        // Colocar la modalidad como texto
        if (modalidad == 'P') strcpy(modalTexto, "PRESENCIAL");
        else if (modalidad == 'V') strcpy(modalTexto, "VIRTUAL");
        else strcpy(modalTexto, "SEMIPRESENCIAL");
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

void imprimirReporteVerificacion() {
    ofstream archReporte = abrirArchSalida("Reporte.txt", false);
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
    imprimirLinea(archReporte, '-');
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
    imprimirLinea(archReporte, '=');
}

void imprimirAlumnos(ofstream &archReporte) {
    ifstream archAlumnos = abrirArchEntrada("Alumnos.bin", true);
    char nomAlu[MAX_NOM_ALU]{}, modalidad[MAX_MODAL];
    int semestre, codAlu, escala;
    double porcVirt, totalCred, costo;
    // Imprimir cabecera
    archReporte << "LISTADO DE ALUMNOS" << endl;
    imprimirLinea(archReporte, '-');
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
    imprimirLinea(archReporte, '=');
}

void imprimirClases(ofstream &archReporte) {
    ifstream archClases  = abrirArchEntrada("ListaDeClases.bin", true);
    char codCur[MAX_COD_CUR]{};
    int semestre, codAlu;
    // Imprimir cabecera
    archReporte << "LISTADO DE CLASES" << endl;
    imprimirLinea(archReporte, '-');
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
    imprimirLinea(archReporte, '=');
}

void imprimirEscalas(ofstream &archReporte) {
    ifstream archEscalas = abrirArchEntrada("Escalas.bin", true);
    double escala;
    // Imprimir cabecera
    archReporte << "LISTADO DE ESCALAS" << endl;
    imprimirLinea(archReporte, '-');
    archReporte << "Monto" << endl;
    // Leer línea por línea
    while (true) {
        archEscalas.read(reinterpret_cast<char *>(&escala), sizeof(double));
        if (archEscalas.eof()) break;
        archReporte << escala << endl;
    }
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

int obtenerNumReg(fstream &arch, int tamReg) {
    arch.seekg(0, ios::end);
    int tamArch = arch.tellg();
    arch.seekg(0, ios::beg);
    return tamArch / tamReg;
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LIN_REP; i++) arch.put(car);
    arch << endl;
}
