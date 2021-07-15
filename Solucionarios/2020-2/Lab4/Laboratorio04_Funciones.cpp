/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 9 de octubre de 2020, 08:48 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Laboratorio04_Funciones.h"
using namespace std;

#define MAX_LINEA 100
#define MAX_MEDICOS 50
#define MAX_PACIENTES 200
#define MAX_PALABRAS 50
#define MAX_CODIGO 7
#define SEP_MEDICOS 70
#define SEP_PACIENTES 50

void cargarMedicos(char** &codigoMed, char** &medicos, double* &tarifas) {
    ifstream arch = abrirArchivoEntrada("RelacionMedicos.csv");
    char *codMedAux[MAX_MEDICOS], *medicosAux[MAX_MEDICOS], buffer[MAX_LINEA];
    double tarifasAux[MAX_MEDICOS], tarifa;
    int numMedicos = 0;
    // Leer los médicos línea por línea
    while (true) {
        // Leer el código del médico
        arch.getline(buffer, MAX_LINEA, ',');
        if (arch.eof()) break;
        codMedAux[numMedicos] = crearCadenaExacta(buffer);
        // Leer el nombre del médico
        arch.getline(buffer, MAX_LINEA, ',');
        medicosAux[numMedicos] = crearCadenaExacta(buffer);
        // Leer e ignorar la especialidad del médico
        arch.getline(buffer, MAX_LINEA, ',');
        // Leer la tarifa del médico
        arch >> tarifa >> ws;
        tarifasAux[numMedicos++] = tarifa;
    }
    // Asignar espacios dinámicos y exactos
    codigoMed = crearArrCadenas(codMedAux, numMedicos);
    medicos = crearArrCadenas(medicosAux, numMedicos);
    tarifas = crearArrDouble(tarifasAux, numMedicos);
}

void reporteMedicos(char** codigoMed, char** medicos, double* tarifas) {
    ofstream arch = abrirArchivoSalida("ReporteMedicos.txt");
    // Imprimir cabecera del reporte
    arch << left << fixed << setprecision(2);
    arch << setw(8) << "Codigo" << setw(50) << "Nombre" << setw(10) << "Tarifas" << endl;
    imprimirLinea(arch, '=', SEP_MEDICOS);
    // Imprimir lista de médicos
    for (int i = 0; codigoMed[i] != nullptr; i++) {
        arch << left << setw(8) << codigoMed[i] << setw(50) << medicos[i];
        arch << right << setw(10) << tarifas[i] << endl;
    }
}

void reporteDeIngresos(char** codigoMed, char** medicos, double* tarifas) {
    int *codigoPac, *veces;
    char **pacientes, codMed[MAX_CODIGO];
    double *porcentajes;
    ifstream archMedicos = abrirArchivoEntrada("Medicos.csv");
    ofstream archReporte = abrirArchivoSalida("ReporteIngresos.txt");
    archReporte << left << fixed << setprecision(2);
    // Iteración por cada médico
    while (true) {
        archMedicos.getline(codMed, MAX_CODIGO);
        if (archMedicos.eof()) break;
        cargarPacientes(codMed, codigoPac, pacientes, porcentajes, veces);
        reporteDelMedico(codMed, codigoMed, medicos, tarifas, codigoPac,
                pacientes, porcentajes, veces, archReporte);
        liberarEspacios(codigoPac, pacientes, porcentajes, veces);
    }
    // Liberar espacios de los médicos
    liberarArrCadenas(codigoMed);
    liberarArrCadenas(medicos);
    delete tarifas;
}

void cargarPacientes(char* codMedBuscado, int* &codigoPac, char** &pacientes,
        double* &porcentajes, int* &veces) {
    // Declaración de variables
    ifstream arch = abrirArchivoEntrada("Pacientes-Atencion.csv");
    char *pacAux[MAX_PACIENTES], nombre[MAX_LINEA], codMedLeido[MAX_CODIGO], c, estado;
    int codPacAux[MAX_PACIENTES], vecesAux[MAX_PACIENTES], numPac = 0, dia, mes, anho, codPac;
    double porcAux[MAX_PACIENTES], porcLeido;
    // Leer línea por línea
    while (true) {
        arch >> dia;
        if (arch.eof()) break;
        if (arch.fail()) {
            arch.clear();
            // Leer los datos del paciente
            arch >> estado >> c >> codPac >> c;
            arch.getline(nombre, MAX_LINEA, ',');
            arch >> porcLeido >> c;
            arch.getline(codMedLeido, MAX_CODIGO, ',');
            if (arch.fail()) arch.clear();
            // Verificar si es un paciente atendido del médico buscado
            if (strcmp(codMedBuscado, codMedLeido) == 0 && estado == 'A') {
                agregarPaciente(codPac, nombre, porcLeido, numPac, codPacAux,
                        pacAux, porcAux, vecesAux);
            }
        } else {
            // Leer e ignorar la fecha de atención
            arch >> c >> mes >> c >> anho >> c;
        }
    }
    // Asignar espacios dinámicos y exactos
    codigoPac = crearArrEnteros(codPacAux, numPac);
    pacientes = crearArrCadenas(pacAux, numPac);
    porcentajes = crearArrDouble(porcAux, numPac);
    veces = crearArrEnteros(vecesAux, numPac);
}

void agregarPaciente(int codPac, char* nombre, double porcLeido, int& numPac,
        int* codPacAux, char** pacAux, double* porcAux, int* vecesAux) {
    // Buscar al paciente en el arreglo, si existe aumentar el número de veces
    for (int i = 0; i < numPac; i++) {
        if (codPacAux[i] == codPac) {
            vecesAux[i]++;
            return;
        }
    }
    // Si no existe, agregarlo a la lista
    codPacAux[numPac] = codPac;
    pacAux[numPac] = crearCadenaExacta(nombre);
    porcAux[numPac] = porcLeido;
    vecesAux[numPac] = 1;
    numPac++;
}

void reporteDelMedico(char* codMed, char** codigoMed, char** medicos,
        double* tarifas, int* codigoPac, char** pacientes,
        double* porcentajes, int* veces, ofstream& arch) {
    // Declaración de variables
    double montoPacientes = 0, montoSeguro = 0;
    int totalCitas = 0;
    // Buscar los datos del médico
    for (int i = 0; codigoMed[i] != nullptr; i++) {
        if (strcmp(codigoMed[i], codMed) == 0) {
            // Imprimir cabecera del médico
            arch << "Medico: " << medicos[i] << endl;
            arch << "Codigo: " << codigoMed[i] << endl;
            arch << "Honorarios por cita: " << tarifas[i] << endl;
            imprimirLinea(arch, '=', SEP_PACIENTES);
            // Imprimir lista de pacientes
            arch << "Pacientes atendidos: " << endl;
            imprimirLinea(arch, '-', SEP_PACIENTES);
            imprimirPacientes(codigoPac, pacientes, porcentajes, veces, tarifas[i],
                    montoPacientes, montoSeguro, totalCitas, arch);
            imprimirLinea(arch, '=', SEP_PACIENTES);
            // Imprimir resumen de pacientes
            arch << "Monto total recibido por pacientes: " << setw(8) << montoPacientes << endl;
            arch << "Monto a solicitar al seguro: " << setw(15) << montoSeguro << endl;
            arch << "Total de citas atendidas: " << setw(15) << totalCitas << endl;
            imprimirLinea(arch, '=', SEP_PACIENTES);
            return;
        }
    }
}

void imprimirPacientes(int* codigoPac, char** pacientes, double* porcentajes,
        int* veces, double tarifa, double& montoPacientes, double& montoSeguro,
        int& totalCitas, ofstream& arch) {
    // Imprimir cabecera
    arch << left << setw(8) << "No." << setw(12) << "Paciente"
            << setw(10) << "Pago" << setw(10) << "Seguro"
            << setw(10) << "Veces" << endl;
    // Imprimir lista de pacientes y sus montos
    for (int j = 0; pacientes[j] != nullptr; j++) {
        // Calcular variables auxiliares
        double pago = tarifa*veces[j]*porcentajes[j]/100;
        double seguro = tarifa*veces[j] - pago;
        int width = j >= 10 ? 5 : 6;
        // Imprimir datos
        arch << left << j << ')' << setw(width) << ' '
                << setw(10) << codigoPac[j]
                << right << setw(8) << pago
                << setw(10) << seguro
                << setw(7) << veces[j] << endl;
        // Actualizar contadores
        montoPacientes += pago;
        montoSeguro += seguro;
        totalCitas += veces[j];
    }
}

void liberarEspacios(int* codigoPac, char** pacientes, double* porcentajes,
        int* veces) {
    // Liberar espacios de los pacientes
    delete codigoPac;
    liberarArrCadenas(pacientes);
    delete porcentajes;
    delete veces;
}

/* Funciones auxiliares */

ifstream abrirArchivoEntrada(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirArchivoSalida(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

char* crearCadenaExacta(char* buffer) {
    char* cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

char** crearArrCadenas(char** arrAux, int num) {
    char** arr = new char*[num + 1];
    for (int i = 0; i < num; i++) {
        arr[i] = arrAux[i];
    }
    arr[num] = nullptr;
    return arr;
}

int* crearArrEnteros(int* arrAux, int num) {
    int* arr = new int[num]; //+1
    for (int i = 0; i < num; i++) {
        arr[i] = arrAux[i];
    }
    // arr[num] = 0;
    return arr;
}

double* crearArrDouble(double* arrAux, int num) {
    double* arr = new double[num]; //+1
    for (int i = 0; i < num; i++) {
        arr[i] = arrAux[i];
    }
    // arr[num] = 0;
    return arr;
}

void liberarArrCadenas(char** arr) {
    for (int i = 0; arr[i] != nullptr; i++) {
        delete arr[i];
    }
    delete arr;
}

void imprimirLinea(ofstream& out, char c, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        out.put(c);
    }
    out << endl;
}
