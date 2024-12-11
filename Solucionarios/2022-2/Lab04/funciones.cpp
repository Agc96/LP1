/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de septiembre de 2022, 01:17 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

#define MAX_MEDICOS 50
#define MAX_NOMBRE 60
#define MAX_PACIENTES 100
#define MAX_CITAS 50
#define MAX_LIN_PRUEBA 80
#define MAX_LIN_REPORTE 105

/* Pregunta 1 */

void lecturaDeMedicos(const char *nomArch, int *&med_Codigo,
        char **&med_Nombre, char **&med_Especialidad, double *&med_Tarifa) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    char *buffNombre[MAX_MEDICOS], *buffEspec[MAX_MEDICOS], nombre[MAX_NOMBRE];
    int buffCodigo[MAX_MEDICOS], numMed = 0;
    double buffTarifa[MAX_MEDICOS];
    // Leer línea por línea
    while (true) {
        arch >> buffCodigo[numMed];
        if (arch.eof()) break;
        arch.get();
        arch.getline(nombre, MAX_NOMBRE, ',');
        procesarNombre(nombre, buffNombre[numMed], buffEspec[numMed]);
        arch >> buffTarifa[numMed];
        numMed++;
    }
    // Crear arreglos dinámicos y exactos
    med_Codigo = new int[numMed+1];
    med_Nombre = new char *[numMed];
    med_Especialidad = new char *[numMed];
    med_Tarifa = new double[numMed];
    for (int i = 0; i < numMed; i++) {
        med_Codigo[i] = buffCodigo[i];
        med_Nombre[i] = buffNombre[i];
        med_Especialidad[i] = buffEspec[i];
        med_Tarifa[i] = buffTarifa[i];
    }
    med_Codigo[numMed] = 0;
}

void procesarNombre(char *linea, char *&nombre, char *&espec) {
    int indice;
    // Buscar el índice donde se ubica el último espacio
    for (int i = 0; linea[i] /* != 0 */; i++) {
        if (linea[i] == ' ') indice = i;
    }
    linea[indice] = 0;
    // Crear nombre y especialidad
    nombre = crearCadenaExacta(linea);
    espec = crearCadenaExacta(&(linea[indice+1]));
}

void pruebaDeLecturaDeMedicos(const char *nomArch, int *med_Codigo,
        char **med_Nombre, char **med_Especialidad, double *med_Tarifa) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    arch << left << fixed << setprecision(2);
    arch << setw(10) << "Codigo" << setw(40) << "Nombre"
            << setw(24) << "Especialidad" << "Tarifa" << endl;
    imprimirLinea(arch, '=', MAX_LIN_PRUEBA);
    for (int i = 0; med_Codigo[i]; i++) {
        arch << left << setw(10) << med_Codigo[i] << setw(40) << med_Nombre[i]
                << setw(24) << med_Especialidad[i]
                << right << setw(6) << med_Tarifa[i] << endl;
    }
}

/* Pregunta 2 */

void lecturaDeCitas(const char *nomArch, int *&pac_Dni, char **&pac_Nombre,
        int **&pac_Citas) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    char *buffNombre[MAX_PACIENTES], nombre[MAX_NOMBRE], c;
    int buffDni[MAX_PACIENTES]{}, *buffCitas[MAX_PACIENTES], dni, codMed,
            dd, mm, aaaa, fecha, indice, numPac = 0;
    // Leer línea por línea
    while (true) {
        arch >> dni >> c;
        if (arch.eof()) break;
        arch.getline(nombre, MAX_NOMBRE, ',');
        arch >> codMed >> c >> dd >> c >> mm >> c >> aaaa;
        fecha = 10000*aaaa + 100*mm + dd;
        // Buscar si el paciente ya está registrado
        indice = buscarEnArreglo(buffDni, dni);
        if (indice != -1) {
            agregarCita(buffCitas[indice], codMed, fecha);
        } else {
            buffDni[numPac] = dni;
            buffNombre[numPac] = crearCadenaExacta(nombre);
            buffCitas[numPac] = new int[MAX_CITAS]{};
            agregarCita(buffCitas[numPac], codMed, fecha);
            numPac++;
        }
    }
    // Crear arreglos dinámicos y exactos
    pac_Dni = new int[numPac+1];
    pac_Nombre = new char *[numPac];
    pac_Citas = new int *[numPac];
    for (int i = 0; i < numPac; i++) {
        pac_Dni[i] = buffDni[i];
        pac_Nombre[i] = buffNombre[i];
        pac_Citas[i] = copiarCitas(buffCitas[i]);
    }
    pac_Dni[numPac] = 0;
}

void agregarCita(int *buffCita, int codMed, int fecha) {
    int tamCitas = obtenerCantDatos(buffCita);
    buffCita[tamCitas] = codMed;
    buffCita[tamCitas+1] = fecha;
}

int *copiarCitas(int *buffCita) {
    int *cita, numCitas;
    // Obtener número de citas para este paciente
    numCitas = obtenerCantDatos(buffCita);
    // Crear arreglo dinámico y exacto
    cita = new int[numCitas+1];
    for (int i = 0; i < numCitas; i++) {
        cita[i] = buffCita[i];
    }
    cita[numCitas] = 0;
    // Borrar arreglo dinámico anterior
    delete[] buffCita;
    return cita;
}

void pruebaDeLecturaDeCitas(const char *nomArch, int *pac_Dni,
        char **pac_Nombre, int **pac_Citas) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    int *cita;
    arch << left << setw(10) << "DNI" << setw(30) << "Nombre"
            << setw(15) << "Medico" << "Fecha" << endl;
    imprimirLinea(arch, '=', MAX_LIN_PRUEBA);
    for (int i = 0; pac_Dni[i] /* != 0 */; i++) {
        arch << left << setw(10) << pac_Dni[i] << setw(30) << pac_Nombre[i];
        cita = pac_Citas[i];
        for (int j = 0; cita[j]; j += 2) {
            if (j > 0) arch << left << setw(40) << ' ';
            arch << setw(15) << cita[j];
            imprimirFecha(arch, cita[j+1]);
            arch << endl;
        }
        imprimirLinea(arch, '-', MAX_LIN_PRUEBA);
    }
}

/* Pregunta 3 */

void reporteDeIngresosMedicosYGastosDeLosPacientes(const char *nomArch,
        int *med_Codigo, char **med_Nombre, char **med_Especialidad,
        double *med_Tarifa, int *pac_Dni, char **pac_Nombre, int **pac_Citas) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    // Imprimir cabecera
    arch << fixed << setprecision(2);
    arch << right << setw(66) << "EMPRESA PRESTADORA DE SALUD" << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    // Imprimir reportes de médicos y pacientes
    reporteFinalDeMedicos(arch, med_Codigo, med_Nombre, med_Especialidad,
            med_Tarifa, pac_Citas);
    reporteFinalDePacientes(arch, pac_Dni, pac_Nombre, pac_Citas, med_Codigo,
            med_Tarifa);
}

void reporteFinalDeMedicos(ofstream &arch, int *med_Codigo, char **med_Nombre,
        char **med_Especialidad, double *med_Tarifa, int **pac_Citas) {
    double ingresos = 0, total = 0;
    // Imprimir cabecera de médicos
    arch << left << "INGRESO DE LOS MEDICOS POR LAS CITAS:" << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    arch << setw(5) << "No." << setw(10) << "Codigo" << setw(40) << "Nombre"
            << setw(24) << "Especialidad" << setw(9) << "Tarifa"
            << "Total de ingresos" << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    // Imprimir listado de médicos
    for (int i = 0; med_Codigo[i] /* != 0 */; i++) {
        ingresos = calcularIngresosMedico(med_Codigo[i], med_Tarifa[i], pac_Citas);
        arch << right << setw(2) << (i+1) << ")  " << left << setw(10)
                << med_Codigo[i] << setw(40) << med_Nombre[i] << setw(24)
                << med_Especialidad[i] << right << setw(6) << med_Tarifa[i]
                << setw(20) << ingresos << endl;
        total += ingresos;
    }
    imprimirLinea(arch, '-', MAX_LIN_REPORTE);
    // Imprimir resumen de médicos
    arch << left << setw(85) << "Total ingresado:" << right << setw(20)
            << total << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
}

double calcularIngresosMedico(int codMed, double tarifa, int **pac_Citas) {
    int *cita;
    double ingresos = 0;
    for (int i = 0; pac_Citas[i] /* != 0 */; i++) {
        cita = pac_Citas[i];
        for (int j = 0; cita[j]; j += 2) {
            if (cita[j] == codMed) ingresos += tarifa;
        }
    }
    return ingresos;
}

void reporteFinalDePacientes(ofstream &arch, int *pac_Dni, char **pac_Nombre,
        int **pac_Citas, int *med_Codigo, double *med_Tarifa) {
    int numCitas;
    double gastos, total = 0;
    // Imprimir cabecera de pacientes
    arch << "GASTOS DE LOS PACIENTES POR LAS CITAS:" << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    arch << left << setw(5) << "No." << setw(10) << "DNI" << setw(25) << "Nombre"
            << setw(20) << "Numero de citas" << "Total de gastos" << endl;
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    // Imprimir listado de pacientes
    for (int i = 0; pac_Dni[i] /* != 0 */; i++) {
        numCitas = obtenerCantDatos(pac_Citas[i]) / 2;
        gastos = obtenerGastosPaciente(pac_Citas[i], med_Codigo, med_Tarifa);
        arch << right << setw(2) << (i+1) << ")  " << left << setw(10)
                << pac_Dni[i] << setw(30) << pac_Nombre[i]
                << right << setw(5) << numCitas << setw(22) << gastos << endl;
        total += gastos;
    }
    imprimirLinea(arch, '=', MAX_LIN_REPORTE);
    // Imprimir resumen de pacientes (no es necesario, pero sirve para corroborar)
    arch << left << setw(50) << "Total gastado:" << right << setw(22)
            << total << endl;
}

double obtenerGastosPaciente(int *citas, int *med_Codigo, double *med_Tarifa) {
    int indMed;
    double gastos = 0;
    for (int i = 0; citas[i] /* != 0 */; i += 2) {
        indMed = buscarEnArreglo(med_Codigo, citas[i]);
        if (indMed != -1) gastos += med_Tarifa[indMed];
    }
    return gastos;
}

/* Funciones auxiliares */

char *crearCadenaExacta(char *linea) {
    char *ptr = new char[strlen(linea)+1];
    strcpy(ptr, linea);
    return ptr;
}

int buscarEnArreglo(int *arr, int dato) {
    for (int i = 0; arr[i]; i++) {
        if (arr[i] == dato) return i;
    }
    return -1;
}

int obtenerCantDatos(int *arr) {
    int cant;
    for (cant = 0; arr[cant]; cant++);
    return cant;
}

void imprimirFecha(ofstream &arch, int fecha) {
    int dd, mm, aaaa;
    dd = fecha % 100;
    mm = (fecha / 100) % 100;
    aaaa = fecha / 10000;
    arch << right << setfill('0') << setw(2) << dd << '/' << setw(2) << mm
            << '/' << setw(4) << aaaa << setfill(' ');
}

void imprimirLinea(ofstream &arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        arch.put(c);
    }
    arch << endl;
}
