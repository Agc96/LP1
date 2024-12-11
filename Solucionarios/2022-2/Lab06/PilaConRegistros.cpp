/*
 * Archivo: PilaConRegistros.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:09 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "PilaConRegistros.h"
using namespace std;

#define MAX_NOMBRE 40
#define MAX_LINEA 55

enum Registro{CODIGO, NOMBRE, PESO};

void *leeregistro(ifstream &arch) {
    int codigo, *ptrCodigo;
    char nombre[MAX_NOMBRE], *ptrNombre;
    double peso, *ptrPeso;
    // Leer datos
    arch >> codigo;
    if (arch.eof()) return nullptr;
    arch.get();
    arch.getline(nombre, MAX_NOMBRE, ',');
    arch >> peso;
    // Transferir datos a punteros
    ptrCodigo = new int;
    *ptrCodigo = codigo;
    ptrNombre = new char[strlen(nombre) + 1];
    strcpy(ptrNombre, nombre);
    ptrPeso = new double;
    *ptrPeso = peso;
    // Almacenar datos en un puntero genérico
    void **dato = new void *[3];
    dato[CODIGO] = ptrCodigo;
    dato[NOMBRE] = ptrNombre;
    dato[PESO] = ptrPeso;
    return dato;
}

int cmpregistro(const void *izq, const void *der) {
    void **auxIzq = (void **)izq, **auxDer = (void **)der;
    auxIzq = (void **)(*auxIzq); auxDer = (void **)(*auxDer);
    double *pesoIzq = (double *)(auxIzq[PESO]), *pesoDer = (double *)(auxDer[PESO]);
    return *pesoDer - *pesoIzq; // descendente para poder apilar más fácil
}

void imprimeregistro(void *dato, ofstream &arch) {
    // Imprimir cabecera
    static bool cabecera = true;
    if (cabecera) {
        arch << left << fixed << setprecision(2);
        arch << setw(10) << "Codigo" << setw(MAX_NOMBRE) << "Nombre"
                << "Peso" << endl;
        imprimeLinea(arch, MAX_LINEA, '=');
        cabecera = false;
    }
    // Obtener los datos de las medicinas
    void **aux = (void **)dato;
    int *codigo = (int *)(aux[CODIGO]);
    char *nombre = (char *)(aux[NOMBRE]);
    double *peso = (double *)(aux[PESO]);
    // Imprimir los datos
    arch << left << setw(10) << *codigo << setw(MAX_NOMBRE) << nombre
            << right << setw(5) << *peso << endl;
}

void imprimeLinea(ofstream &arch, int num, char car) {
    for (int i = 0; i < num; i++) arch.put(car);
    arch << endl;
}
