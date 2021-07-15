/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 07:50 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "PriorityQueue.h"
#include "funciones.h"
using namespace std;

#define MAX_PACIENTES 100
#define MAX_NOMBRE 40
#define MAX_LINEA 120

enum posPaciente{POS_DNI, POS_NOMBRE, POS_ESPEC, POS_PAGO, POS_TIPO};

/* Parte 1: Leer pagos */

void leerTarifas(int *&arrCodEspec, double *&arrTarifas) {
    ifstream arch("Tarifas.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Tarifas.txt" << endl;
        exit(1);
    }
    // Colocar los datos del archivo en búferes
    int buffCodEspec[MAX_PACIENTES], numPac = 0, codEspec;
    double buffTarifas[MAX_PACIENTES], tarifa;
    while (true) {
        arch >> codEspec >> tarifa;
        if (arch.eof()) break;
        buffCodEspec[numPac] = codEspec;
        buffTarifas[numPac] = tarifa;
        numPac++;
    }
    // Copiar los datos de los búferes en arreglos dinámicos y exactos
    arrCodEspec = new int[numPac+1];
    arrTarifas = new double[numPac+1];
    for (int i = 0; i < numPac; i++) {
        arrCodEspec[i] = buffCodEspec[i];
        arrTarifas[i] = buffTarifas[i];
    }
    arrCodEspec[numPac] = 0;
    arrTarifas[numPac] = 0;
}

/* Parte 2: Leer pacientes */

void leerPacientes(void *&cola, int *arrCodEspec, double *arrTarifas) {
    ifstream arch("Pacientes.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Pacientes.csv" << endl;
        exit(1);
    }
    int dni, espec;
    char tipo, nombre[MAX_NOMBRE];
    double porcSeguro, porcDesc;
    void *prioridad, *paciente;
    // Encolar línea por línea
    inicializar(cola);
    while (true) {
        leerDatos(arch, dni, nombre, tipo, espec, porcSeguro, porcDesc);
        if (arch.eof()) break;
        // Formar el nodo
        prioridad = crearPunteroChar(tipo);
        paciente = crearPaciente(dni, nombre, espec, porcSeguro, porcDesc,
                arrCodEspec, arrTarifas, tipo);
        // Encolar el nodo en la cola
        encolar(cola, prioridad, paciente, compararPacientes);
    }
}

void leerDatos(istream &arch, int &dni, char *nombre, char &tipo,
        int &espec, double &porcSeguro, double &porcDesc) {
    char c;
    // Leer datos obligatorios
    arch >> dni >> c;
    if (arch.eof()) return;
    arch.getline(nombre, MAX_NOMBRE, ',');
    arch >> tipo >> c >> espec;
    // Leer porcentajes dependiendo del tipo de paciente
    switch (tipo) {
        case 'U':
            arch >> c >> porcSeguro >> c >> porcDesc;
            break;
        case 'A':
            arch >> c >> porcSeguro;
            porcDesc = 0;
            break;
        case 'E':
            porcSeguro = porcDesc = 0;
            break;
    }
    // Ignorar el siguiente caracter, sea coma (,) o cambio de línea (\n)
    arch.get();
}

void *crearPaciente(int dni, char *nombre, int espec, double porcSeguro,
        double porcDesc, int *arrCodEspec, double *arrTarifas, char tipo) {
    // Crear el nodo del pago para el paciente
    double pago = buscarTarifa(arrCodEspec, arrTarifas, espec);
    pago = pago * porcSeguro * (100-porcDesc) / 10000;
    // Crear el nodo del paciente
    void **paciente = new void*[5];
    paciente[POS_DNI] = crearPunteroInt(dni);
    paciente[POS_NOMBRE] = crearPunteroCadena(nombre);
    paciente[POS_ESPEC] = crearPunteroInt(espec);
    paciente[POS_PAGO] = crearPunteroDouble(pago);
    paciente[POS_TIPO] = crearPunteroChar(tipo);
    return paciente;
}

double buscarTarifa(int *arrCodEspec, double *arrPago, int codEspecBuscar) {
    for (int i = 0; arrCodEspec[i] != 0; i++) {
        if (arrCodEspec[i] == codEspecBuscar) return arrPago[i];
    }
    return 0;
}

int compararPacientes(void *izq, void *der) {
    return convertirTipoPaciente(izq) - convertirTipoPaciente(der);
}

int convertirTipoPaciente(void *tipo) {
    char *tipoChar = (char*)tipo;
    switch (*tipoChar) {
        case 'E':
            return 3;
        case 'U':
            return 2;
        case 'A':
            return 1;
        default:
            return 0;
    }
}

/* Parte 3: Atender pacientes */

void atenderPacientes(void *cola) {
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    // Imprimir cabecera
    arch << fixed << setprecision(2);
    arch << setw(10) << "ATENCION DE PACIENTES" << endl;
    separacion(arch, '=');
    arch << left << setw(8) << "No." << setw(12) << "DNI";
    arch << setw(40) << "Paciente" << setw(16) << "Especialidad";
    arch << setw(12) << "Pago" << "Tipo" << endl;
    // Atender la cola de pacientes
    void *paciente;
    double total = 0;
    int indice = 1;
    while (!esVacia(cola)) {
        paciente = desencolar(cola, eliminarPrioridad);
        imprimirPaciente(arch, paciente, indice, total);
        indice++;
    }
    // Imprimir resumen
    separacion(arch, '=');
    arch << "Total cobrado: " << total << endl;
}

void imprimirPaciente(ostream &arch, void *ptPaciente, int indice, double &total) {
    void **paciente = (void **)ptPaciente;
    int *dni = (int *)(paciente[POS_DNI]);
    char *nombre = (char *)(paciente[POS_NOMBRE]);
    int *espec = (int *)(paciente[POS_ESPEC]);
    double *pago = (double *)(paciente[POS_PAGO]);
    char *tipo = (char *)(paciente[POS_TIPO]);
    // Imprimir los datos del paciente
    arch << right << setw(3) << indice << ')' << setw(4) << ' ';
    arch << left << setw(8) << *dni << setw(4) << ' ';
    arch << setw(MAX_NOMBRE) << nombre << setw(4) << ' ';
    arch << setw(4) << *espec << setw(8) << ' ';
    arch << right << setw(6) << *pago << setw(4) << ' ';
    imprimirTipoPaciente(arch, *tipo);
    // Calcular el total
    total += *pago;
    // Eliminar los espacios de memoria
    delete dni;
    delete nombre;
    delete espec;
    delete pago;
    delete tipo;
    delete paciente;
}

void imprimirTipoPaciente(ostream &arch, char tipo) {
    switch (tipo) {
        case 'E':
            arch << "Emergencia";
            break;
        case 'U':
            arch << "Urgencia";
            break;
        case 'A':
            arch << "Ambulatorio";
            break;
    }
    arch << endl;
}

void eliminarPrioridad(void *prioridad) {
    char *prioridadChar = (char *)prioridad;
    delete prioridadChar;
}

/* Parte 4: Limpiar espacios */

void limpiarEspacios(void *ptCola, int *arrCodEspec, double *arrPagoPac) {
    void **cola = (void **)ptCola;
    delete cola;
    delete arrCodEspec;
    delete arrPagoPac;
}

/* Funciones auxiliares */

char *crearPunteroChar(char valor) {
    char *puntero = new char;
    *puntero = valor;
    return puntero;
}

int *crearPunteroInt(int valor) {
    int *puntero = new int;
    *puntero = valor;
    return puntero;
}

double *crearPunteroDouble(double valor) {
    double *puntero = new double;
    *puntero = valor;
    return puntero;
}

char *crearPunteroCadena(char *cadena) {
    char *puntero = new char[strlen(cadena)+1];
    strcpy(puntero, cadena);
    return puntero;
}

void separacion(ostream &out, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        out.put(c);
    }
    out << endl;
}
