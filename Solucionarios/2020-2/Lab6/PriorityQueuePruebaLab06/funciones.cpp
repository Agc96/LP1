/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 12:10 PM
 */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include "funciones.h"
using namespace std;

#define MAX_LINEA 40

void leerNumeros(void *&cola) {
    ifstream arch("Prueba.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    int prioridad, valor, *ptrPrioridad, *ptrValor;
    while (true) {
        arch >> prioridad >> valor;
        if (arch.eof()) break;
        ptrPrioridad = crearPunteroInt(prioridad);
        ptrValor = crearPunteroInt(valor);
        encolar(cola, ptrPrioridad, ptrValor, ordenarEnteros);
    }
}

int *crearPunteroInt(int valor) {
    int *puntero = new int;
    *puntero = valor;
    return puntero;
}

int ordenarEnteros(void *izq, void *der) {
    int *izqInt = (int*)izq, *derInt = (int*)der;
    return (*izqInt) - (*derInt);
}

void imprimirReporte(void *cola) {
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    // Imprimir usando la función de prueba
    arch << "USANDO LA FUNCION DE PRUEBA" << endl;
    separacion(arch, '-');
    prueba(cola, arch, imprimirEnteros);
    arch << endl;
    // Imprimir usando la función de atención
    void *valor;
    int *valorInt;
    arch << "USANDO LA FUNCION DE ATENCION" << endl;
    separacion(arch, '-');
    while (!esVacia(cola)) {
        valor = desencolar(cola);
        valorInt = (int*)valor;
        arch << "Dato atendido: " << *valorInt << endl;
    }
}

void imprimirEnteros(ostream &arch, void *prioridad, void *valor) {
    int *prioridadInt = (int*)prioridad, *valorInt = (int*)valor;
    arch << "Prioridad: " << *prioridadInt << ", valor: " << *valorInt << endl;
}

void separacion(ostream &arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        arch.put(c);
    }
    arch << endl;
}
