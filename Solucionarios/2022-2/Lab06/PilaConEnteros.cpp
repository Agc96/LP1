/*
 * Archivo: PilaConEnteros.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:09 PM
 */

#include <iostream>
#include <fstream>
#include "PilaConEnteros.h"
using namespace std;

void *leenumero(ifstream &arch) {
    int num, *ptr;
    arch >> num;
    if (arch.eof()) return nullptr;
    ptr = new int;
    *ptr = num;
    return ptr;
}

int cmpnumero(const void *izq, const void *der) {
    void **auxIzq = (void **)izq, **auxDer = (void **)der;
    int *numIzq = (int *)(*auxIzq), *numDer = (int *)(*auxDer);
    return *numDer - *numIzq; // descendente para poder apilar más fácil
}

void imprimenumero(void *dato, ofstream &arch) {
    int *num = (int *)dato;
    arch << *num << endl;
}
