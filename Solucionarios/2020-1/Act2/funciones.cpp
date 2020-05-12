/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 8 de mayo de 2020, 04:42 PM
 */

#include "funciones.h"
#define MAX_LINEA 120
#define MAX_NOMBRE 35
#define MAX_ESPEC 25
#define MAX_FACU 5
#define TAM_ALUMNO (2*sizeof(int) + sizeof(char) + MAX_NOMBRE + MAX_FACU + MAX_ESPEC)
#define TAM_CONSOLIDADO (4*sizeof(int) + MAX_NOMBRE + 2*sizeof(double) + MAX_FACU)
#define MIN_APROBATORIO 11
#define MIN_EGRESADO 45
#define MAX_COD 10
#define MAX_CRED 20
#define MAX_PROM 10
#define MAX_ESTADO 10
#define MAX_RESUMEN 35
#define MAX_TOTAL 5
#define TAM_ESPACIO 2

/* Parte 1: Crear el archivo binario de alumnos */

void transferirArchivoAlumnos(const char* nomArchBin, const char* nomArchTexto) {
    // Declaración de variables
    ifstream archTexto(nomArchTexto, ios::in);
    validarArchivo(archTexto, nomArchTexto);
    ofstream archBin(nomArchBin, ios::out | ios::binary);
    validarArchivo(archBin, nomArchBin);
    // Declaración de variables
    char tipo, nombre[MAX_NOMBRE], espec[MAX_ESPEC], facu[MAX_FACU];
    int codigo, carne;
    // Leer los datos de cada alumno
    while (true) {
        archTexto >> tipo;
        if (archTexto.eof()) break;
        archTexto >> codigo >> ws >> nombre >> carne;
        if (archTexto.fail()) {
            archTexto.clear();
            carne = 0;
        }
        archTexto >> ws >> espec >> ws >> facu;
        // Guardar los datos del alumno
        archBin.write(reinterpret_cast<const char*>(&codigo), sizeof(int));
        archBin.write(nombre, MAX_NOMBRE);
        archBin.write(reinterpret_cast<const char*>(&tipo), sizeof(char));
        archBin.write(reinterpret_cast<const char*>(&carne), sizeof(int));
        archBin.write(facu, MAX_FACU);
        archBin.write(espec, MAX_ESPEC);
    }
}

/* Parte 2: Crear el archivo consolidado */

void crearArchivoConsolidado(const char* nomConsolidado, const char* nomAlumnos) {
    // Apertura de archivos
    ifstream alumnos(nomAlumnos, ios::in | ios::binary);
    validarArchivo(alumnos, nomAlumnos);
    ofstream consolidado(nomConsolidado, ios::out | ios::binary);
    validarArchivo(consolidado, nomConsolidado);
    int cantAlumnos = obtenerCantArchBin(alumnos, TAM_ALUMNO);
    // Declaración de variables
    char nombre[MAX_NOMBRE], facu[MAX_FACU];
    int codigo, dummyI = 0;
    double dummyD = 0;
    // Leer los datos de los alumnos del archivo
    for (int i = 0; i < cantAlumnos; i++) {
        alumnos.seekg(i * TAM_ALUMNO, ios::beg);
        alumnos.read(reinterpret_cast<char*>(&codigo), sizeof(int));
        alumnos.read(nombre, MAX_NOMBRE);
        alumnos.seekg(sizeof(char) + sizeof(int), ios::cur);
        alumnos.read(facu, MAX_FACU);
        // Guardar los datos en el archivo de consolidado
        consolidado.write(reinterpret_cast<const char*>(&codigo), sizeof(int));
        consolidado.write(nombre, MAX_NOMBRE);
        consolidado.write(reinterpret_cast<const char*>(&dummyD), sizeof(double));
        consolidado.write(reinterpret_cast<const char*>(&dummyD), sizeof(double));
        consolidado.write(reinterpret_cast<const char*>(&dummyI), sizeof(int));
        consolidado.write(reinterpret_cast<const char*>(&dummyI), sizeof(int));
        consolidado.write(facu, MAX_FACU);
        consolidado.write(reinterpret_cast<const char*>(&dummyI), sizeof(int));
    }
}

void actualizarArchivoConsolidado(const char* nomConsolidado, const char* nomCursos) {
    // Apertura de archivos
    ifstream cursos(nomCursos, ios::in);
    validarArchivo(cursos, nomCursos);
    fstream consolidado(nomConsolidado, ios::in | ios::out | ios::binary);
    validarArchivo(consolidado, nomConsolidado);
    int cantAlumnos = obtenerCantArchBin(consolidado, TAM_CONSOLIDADO);
    // Declaración de variables
    char curso[MAX_COD], semestre[MAX_COD];
    int alumno, alumnoLeido, nota;
    double creditos;
    // Leer los datos de todos los cursos
    while (true) {
        cursos >> alumno;
        if (cursos.eof()) break;
        cursos >> ws >> curso >> nota >> ws >> semestre >> creditos;
        // Buscar el código del alumno en el consolidado
        for (int i = 0; i < cantAlumnos; i++) {
            consolidado.seekg(i * TAM_CONSOLIDADO, ios::beg);
            consolidado.read(reinterpret_cast<char*>(&alumnoLeido), sizeof(int));
            if (alumnoLeido == alumno) {
                actualizarAlumnoConsolidado(consolidado, i, creditos, nota);
                break;
            }
        }
    }
}

void actualizarAlumnoConsolidado(fstream& consolidado, int indiceAlumno,
        double creditos, int nota) {
    // Declaración de variables
    int sumaNotas, cantMaterias, egresado = 1;
    double credCursados, credAprobados;
    // Obtener los datos que se actualizarán
    consolidado.seekg(MAX_NOMBRE, ios::cur);
    consolidado.read(reinterpret_cast<char*>(&credCursados), sizeof(double));
    consolidado.read(reinterpret_cast<char*>(&credAprobados), sizeof(double));
    consolidado.read(reinterpret_cast<char*>(&sumaNotas), sizeof(int));
    consolidado.read(reinterpret_cast<char*>(&cantMaterias), sizeof(int));
    // Actualizar los datos
    credCursados += creditos;
    sumaNotas += nota;
    cantMaterias++;
    if (nota >= MIN_APROBATORIO) {
        credAprobados += creditos;
    }
    // Grabar los datos actualizados en el consolidado
    consolidado.seekg(indiceAlumno * TAM_CONSOLIDADO + sizeof(int) + MAX_NOMBRE, ios::beg);
    consolidado.write(reinterpret_cast<const char*>(&credCursados), sizeof(double));
    consolidado.write(reinterpret_cast<const char*>(&credAprobados), sizeof(double));
    consolidado.write(reinterpret_cast<const char*>(&sumaNotas), sizeof(int));
    consolidado.write(reinterpret_cast<const char*>(&cantMaterias), sizeof(int));
    if (credAprobados >= MIN_EGRESADO) {
        consolidado.seekg(MAX_FACU, ios::cur);
        consolidado.write(reinterpret_cast<const char*>(&egresado), sizeof(int));
    }
}

/* Parte 3: Generar reporte consolidado */

void generarReporteConsolidado(const char* nomReporte, const char* nomArchAlumnos,
        const char* nomConsolidado) {
    // Apertura de archivos
    ifstream archAlumnos(nomArchAlumnos, ios::in | ios::binary);
    validarArchivo(archAlumnos, nomArchAlumnos);
    ifstream consolidado(nomConsolidado, ios::in | ios::binary);
    validarArchivo(consolidado, nomConsolidado);
    ofstream reporte(nomReporte, ios::out);
    validarArchivo(reporte, nomReporte);
    int cantAlumnos = obtenerCantArchBin(consolidado, TAM_CONSOLIDADO);
    // Declaración de variables
    char tipo, nombre[MAX_NOMBRE];
    int codigo, carne, sumaNotas, cantMaterias, estado, totalRegulares = 0,
            totalIntercambio = 0, cantEgresados = 0, intercambioSinCarne = 0;
    double credCursados, credAprobados;
    // Imprimir cabecera
    imprimirCabeceraReporte(reporte);
    // Imprimir datos de los alumnos
    for (int i = 0; i < cantAlumnos; i++) {
        // Leer los datos del archivo consolidado
        consolidado.seekg(i*TAM_CONSOLIDADO, ios::beg);
        consolidado.read(reinterpret_cast<char*>(&codigo), sizeof(int));
        consolidado.read(nombre, MAX_NOMBRE);
        consolidado.read(reinterpret_cast<char*>(&credCursados), sizeof(double));
        consolidado.read(reinterpret_cast<char*>(&credAprobados), sizeof(double));
        consolidado.read(reinterpret_cast<char*>(&sumaNotas), sizeof(int));
        consolidado.read(reinterpret_cast<char*>(&cantMaterias), sizeof(int));
        consolidado.seekg(MAX_FACU, ios::cur);
        consolidado.read(reinterpret_cast<char*>(&estado), sizeof(int));
        // Leer los datos faltantes del archivo de alumnos
        archAlumnos.seekg(i*TAM_ALUMNO + sizeof(int) + MAX_NOMBRE, ios::beg);
        archAlumnos.read(reinterpret_cast<char*>(&tipo), sizeof(char));
        archAlumnos.read(reinterpret_cast<char*>(&carne), sizeof(int));
        // Imprimir los datos requeridos
        imprimirAlumnoReporte(reporte, codigo, nombre, carne, credCursados,
                credAprobados, (double)sumaNotas/cantMaterias, estado);
        // Calcular las estadísticas
        if (tipo == 'R') {
            totalRegulares++;
        } else {
            totalIntercambio++;
            if (carne == 0) {
                intercambioSinCarne++;
            }
        }
        if (estado > 0) {
            cantEgresados++;
        }
    }
    // Imprimir resumen
    imprimirResumenReporte(reporte, totalRegulares, totalIntercambio,
            cantEgresados, intercambioSinCarne);
}

void imprimirCabeceraReporte(ofstream& reporte) {
    reporte << fixed << setprecision(2);
    // Imprimir el título del reporte
    reporte << left << "CONSOLIDADO DE NOTAS DE LOS ALUMNOS" << endl;
    separador(reporte);
    // Imprimir los títulos de las columnas del reporte
    reporte << setw(MAX_COD) << "CODIGO"
            << setw(MAX_NOMBRE) << "NOMBRE"
            << setw(MAX_COD) << "CARNE"
            << setw(MAX_CRED) << "CRED. CURSADOS"
            << setw(MAX_CRED) << "CRED. APROBADOS"
            << setw(MAX_PROM) << "PROMEDIO"
            << setw(MAX_ESTADO) << "ESTADO" << endl;
    separador(reporte);
}

void imprimirAlumnoReporte(ofstream& reporte, int codigo, char* nombre, int carne,
        double credCursados, double credAprobados, double promedio, int estado) {
    // Imprimir código del alumno
    reporte << right << setfill('0') << setw(MAX_COD - TAM_ESPACIO) << codigo;
    espacios(reporte, TAM_ESPACIO);
    // Imprimir el nombre del alumno
    reporte << left << setfill(' ') << setw(MAX_NOMBRE) << nombre;
    // Imprimir el número de carné del alumno, de ser necesario
    if (carne > 0) {
        reporte << setw(MAX_COD) << carne;
    } else {
        espacios(reporte, MAX_COD);
    }
    // Imprimir los créditos cursados y aprobados
    reporte << right << setw(MAX_CRED - TAM_ESPACIO) << credCursados;
    reporte << setw(MAX_CRED) << credAprobados;
    // Imprimir el promedio de notas
    reporte << setw(MAX_PROM) << promedio;
    espacios(reporte, TAM_ESPACIO);
    // Imprimir el estado del alumno
    reporte << (estado ? "EGRESADO" : "NO EGRESADO") << endl;
}

void imprimirResumenReporte(ofstream& reporte, int totalRegulares,
        int totalIntercambio, int cantEgresados, int cantCarne) {
    separador(reporte);
    reporte << "RESUMEN:" << endl;
    reporte << left << setw(MAX_RESUMEN) << "TOTAL DE ALUMNOS REGULARES:"
            << right << setw(MAX_TOTAL) << totalRegulares << endl;
    reporte << left << setw(MAX_RESUMEN) << "TOTAL DE ALUMNOS DE INTERCAMBIO:"
            << right << setw(MAX_TOTAL) << totalIntercambio << endl;
    reporte << left << setw(MAX_RESUMEN) << "EGRESADOS:"
            << right << setw(MAX_TOTAL) << cantEgresados << endl;
    reporte << left << setw(MAX_RESUMEN) << "ALUMNOS DE INTERCAMBIO SIN CARNE:"
            << right << setw(MAX_TOTAL) << cantCarne << endl;
    separador(reporte);
}

/* Funciones auxiliares */

void validarArchivo(ios& archivo, const char* nombre) {
    if (!archivo) {
        cerr << "No se puede abrir el archivo " << nombre << '.' << endl;
        exit(1);
    }
}

int obtenerCantArchBin(istream& arch, int tamRegistro) {
    arch.seekg(0, ios::end);
    int tamArchivo = arch.tellg() / tamRegistro;
    arch.seekg(0, ios::beg);
    return tamArchivo;
}

void separador(ostream& archivo) {
    repetir(archivo, '=', MAX_LINEA, true);
}

void espacios(ostream& archivo, int cantidad) {
    repetir(archivo, ' ', cantidad, false);
}

void repetir(ostream& archivo, char c, int cantidad, bool agregarFinLinea) {
    for (int i = 0; i < cantidad; i++) {
        archivo << c;
    }
    if (agregarFinLinea) {
        archivo << endl;
    }
}
