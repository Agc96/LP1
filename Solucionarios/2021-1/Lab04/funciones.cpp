/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 15 de mayo de 2021, 12:39 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "funciones.h"
using namespace std;

#define MAX_CONDUCTORES 120
#define MAX_INFRACCIONES 120
#define MAX_FALTAS 250
#define MAX_BUFFER 200
#define MAX_PLACA 10
#define MAX_LIN_COND 50
#define MAX_LIN_INF 30
#define MAX_LIN_FAL 40

/* Pregunta 1 */

void cargarConductores(int*& licencia, char**& conductor) {
    ifstream arch = abrirArchivo("Conductores.csv");
    int auxArrLic[MAX_CONDUCTORES], num = 0, codLic;
    char *auxArrCond[MAX_CONDUCTORES], c, nombre[MAX_BUFFER];
    // Leer los datos del archivo línea por línea
    while (1) {
        arch >> codLic >> c;
        if (arch.eof()) break;
        arch.getline(nombre, MAX_BUFFER);
        // Colocar los datos en los arreglos
        auxArrLic[num] = codLic;
        auxArrCond[num] = crearCadenaExacta(nombre);
        num++;
    }
    // Crear los arreglos dinámicos y estáticos
    crearArrConductoresExactos(licencia, conductor, auxArrLic, auxArrCond, num);
}

void crearArrConductoresExactos(int*& licencia, char**& conductor,
        int* auxLicencia, char** auxConductor, int num) {
    licencia = new int[num+1];
    conductor = new char*[num+1];
    for (int i = 0; i < num; i++) {
        licencia[i] = auxLicencia[i];
        conductor[i] = auxConductor[i];
    }
    licencia[num] = -1;
    conductor[num] = nullptr;
}

void reporteConductores(int* licencia, char** conductor) {
    ofstream arch = crearArchivo("ReporteConductores.txt");
    // Imprimir cabecera
    arch << left << fixed << setprecision(2);
    arch << setw(12) << "LICENCIA" << "CONDUCTOR" << endl;
    imprimirLinea(arch, '=', MAX_LIN_COND);
    // Imprimir lista de conductores
    for (int i = 0; conductor[i]; i++) {
        arch << setw(12) << licencia[i] << conductor[i] << endl;
    }
}

/* Pregunta 2 */

void cargarInfracciones(int*& infraccion, char*& gravedad, double*& multa) {
    ifstream arch = abrirArchivo("Infracciones.csv");
    int auxInfraccion[MAX_INFRACCIONES], codInf, num = 0;
    char auxGravedad[MAX_INFRACCIONES], buffer[MAX_BUFFER], c;
    double auxMulta[MAX_INFRACCIONES], monto;
    // Leer los datos del archivo línea por línea
    while (1) {
        arch >> codInf >> c;
        if (arch.eof()) break;
        arch.getline(buffer, MAX_BUFFER, ','); // Ignorar nombre
        arch.getline(buffer, MAX_BUFFER, ','); // Obtener la gravedad
        arch >> monto;
        // Colocar los datos en los arreglos
        auxInfraccion[num] = codInf;
        auxGravedad[num] = buffer[0];
        auxMulta[num] = monto;
        num++;
    }
    // Crear los arreglos dinámicos y estáticos
    crearArrInfraccionesExactos(infraccion, gravedad, multa, auxInfraccion,
            auxGravedad, auxMulta, num);
}

void crearArrInfraccionesExactos(int*& infraccion, char*& gravedad,
        double*& multa, int* auxInfraccion, char* auxGravedad,
        double* auxMulta, int num) {
    infraccion = new int[num+1];
    gravedad = new char[num+1];
    multa = new double[num+1];
    for (int i = 0; i < num; i++) {
        infraccion[i] = auxInfraccion[i];
        gravedad[i] = auxGravedad[i];
        multa[i] = auxMulta[i];
    }
    infraccion[num] = -1;
    gravedad[num] = '\0';
    multa[num] = 0;
}

void reporteInfracciones(int* infraccion, char* gravedad, double* multa) {
    ofstream arch = crearArchivo("ReporteInfracciones.txt");
    // Imprimir cabecera
    arch << left << fixed << setprecision(2);
    arch << setw(10) << "CODIGO" << setw(12) << "GRAVEDAD" << "MULTA" << endl;
    imprimirLinea(arch, '=', MAX_LIN_INF);
    // Imprimir lista de infracciones
    for (int i = 0; infraccion[i] != -1; i++) {
        arch << left << setw(10) << infraccion[i] << setw(12) << gravedad[i];
        arch << right << setw(8) << multa[i] << endl;
    }
}

/* Pregunta 3 */

void reporteDeFaltas(int* licencia, char** conductor, int* infraccion,
        char* gravedad, double* multa) {
    ofstream arch = crearArchivo("ReporteFaltas.txt");
    int *arrLicFaltas, *arrCant;
    char **arrPlaca;
    double *arrMonto;
    // Generar el reporte por cada tipo de falta
    arch << left << fixed << setprecision(2);
    for (int i = 0; i < 3; i++) {
        cargarFaltasPorGravedad(infraccion, gravedad, multa, arrLicFaltas,
                arrPlaca, arrCant, arrMonto, obtenerTipoGravedad(i));
        reporteFaltasPorGravedad(arch, arrLicFaltas, arrPlaca, arrCant, arrMonto, i);
        liberarEspaciosFaltas(arrLicFaltas, arrPlaca, arrCant, arrMonto);
    }
    // Liberar espacios de los arreglos principales ya que aquí termina el programa
    liberarEspaciosCondInf(licencia, conductor, infraccion, gravedad, multa);
}

void cargarFaltasPorGravedad(int* infraccion, char* gravedad, double* multa,
        int*& arrLicFaltas, char**& arrPlaca, int*& arrCant, double*& arrMonto,
        char tipoGrav) {
    ifstream arch = abrirArchivo("RegistroDeFaltas.csv");
    int auxArrLicFaltas[MAX_FALTAS], auxArrCant[MAX_FALTAS];
    char *auxArrPlaca[MAX_FALTAS], bufPlaca[MAX_PLACA], c;
    double auxArrMonto[MAX_FALTAS];
    int codLic, codInf, aux, indInf, num = 0;
    while (1) {
        arch >> codLic >> c;
        if (arch.eof()) break;
        arch.getline(bufPlaca, MAX_PLACA, ','); 
        arch >> aux >> c >> aux >> c >> aux >> c >> codInf;
        // Buscar el tipo de gravedad según la infracción
        indInf = buscarInfraccion(infraccion, codInf);
        if (indInf != -1 && gravedad[indInf] == tipoGrav) {
            agregarFalta(auxArrLicFaltas, auxArrPlaca, auxArrCant, auxArrMonto,
                    codLic, bufPlaca, multa[indInf], num);
        }
    }
    crearArrFaltasExactos(arrLicFaltas, arrPlaca, arrCant, arrMonto,
            auxArrLicFaltas, auxArrPlaca, auxArrCant, auxArrMonto, num);
}

void agregarFalta(int* arrLicFaltas, char** arrPlaca, int* arrCant,
        double* arrMonto, int codLic, char* placa, double multa, int& num) {
    // Buscar la licencia y la placa en los arreglos
    int indFalta = buscarLicFalta(arrLicFaltas, arrPlaca, codLic, placa, num);
    if (indFalta != -1) {
        // Actualizar cantidad de faltas y monto total
        arrCant[indFalta]++;
        arrMonto[indFalta] += multa;
    } else {
        // Agregar falta al final de la lista
        arrLicFaltas[num] = codLic;
        arrPlaca[num] = crearCadenaExacta(placa);
        arrCant[num] = 1;
        arrMonto[num] = multa;
        num++;
    }
}

void crearArrFaltasExactos(int*& arrLicFaltas, char**& arrPlaca, int*& arrCant,
        double*& arrMonto, int* auxArrLicFaltas, char** auxArrPlaca,
        int* auxArrCant, double* auxArrMonto, int num) {
    arrLicFaltas = new int[num+1];
    arrPlaca = new char*[num+1];
    arrCant = new int[num+1];
    arrMonto = new double[num+1];
    for (int i = 0; i < num; i++) {
        arrLicFaltas[i] = auxArrLicFaltas[i];
        arrPlaca[i] = auxArrPlaca[i];
        arrCant[i] = auxArrCant[i];
        arrMonto[i] = auxArrMonto[i];
    }
    arrLicFaltas[num] = -1;
    auxArrPlaca[num] = nullptr;
    auxArrCant[num] = -1;
    auxArrMonto[num] = -1;
}

char obtenerTipoGravedad(int indice) {
    switch (indice) {
        case 0:
            return 'L';
        case 1:
            return 'G';
        case 2:
            return 'M';
    }
    return 0;
}

int buscarInfraccion(int* arrInfraccion, int infraccion) {
    for (int i = 0; arrInfraccion[i] != -1; i++) {
        if (arrInfraccion[i] == infraccion) return i;
    }
    return -1;
}

int buscarLicFalta(int* arrLicFalta, char** arrPlaca, int licFalta, char* placa, int num) {
    for (int i = 0; i < num; i++) {
        if (arrLicFalta[i] == licFalta && strcmp(arrPlaca[i], placa) == 0) {
            return i;
        }
    }
    return -1;
}

void reporteFaltasPorGravedad(ofstream& arch, int* arrLicFaltas,
        char** arrPlaca, int* arrCant, double* arrMonto, int gravedad) {
    int width, indice;
    imprimirCabeceraFaltas(arch, gravedad);
    for (int i = 0; arrLicFaltas[i] != -1; i++) {
        indice = i+1;
        if (indice >= 100) {
            width = 2;
        } else if (indice >= 10) {
            width = 3;
        } else {
            width = 4;
        }
        arch << left << indice << setw(width) << ')';
        arch << left << setw(10) << arrLicFaltas[i] << setw(9) << arrPlaca[i];
        arch << right << setw(5) << arrCant[i] << setw(11) << arrMonto[i];
        arch << endl;
    }
    imprimirLinea(arch, '*', MAX_LIN_FAL);
}

void imprimirCabeceraFaltas(ofstream& arch, int gravedad) {
    switch (gravedad) {
        case 0:
            arch << left << "FALTAS LEVES" << endl;
            break;
        case 1:
            arch << left << "FALTAS GRAVES" << endl;
            break;
        case 2:
            arch << left << "FALTAS MUY GRAVES" << endl;
            break;
    }
    imprimirLinea(arch, '=', MAX_LIN_FAL);
    arch << setw(5) << "No." << setw(10) << "Licencia" << setw(9) << "Placa";
    arch << setw(10) << "Cantidad" << "Monto" << endl;
    imprimirLinea(arch, '-', MAX_LIN_FAL);
}

void liberarEspaciosFaltas(int* arrLicFaltas, char** arrPlaca, int* arrCant,
        double* arrMonto) {
    delete arrLicFaltas;
    for (int i = 0; arrPlaca[i]; i++) {
        delete arrPlaca[i];
    }
    delete arrPlaca;
    delete arrCant;
    delete arrMonto;
}

void liberarEspaciosCondInf(int* licencia, char** conductor, int* infraccion,
        char* gravedad, double* multa) {
    delete licencia;
    for (int i = 0; conductor[i]; i++) {
        delete conductor[i];
    }
    delete conductor;
    delete infraccion;
    delete gravedad;
    delete multa;
}

/* Funciones auxiliares */

ifstream abrirArchivo(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream crearArchivo(const char* nomArch) {
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

void imprimirLinea(ofstream& arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        arch.put(c);
    }
    arch << endl;
}
