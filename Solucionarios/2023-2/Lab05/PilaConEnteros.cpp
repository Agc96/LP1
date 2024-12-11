/* 
 * File:   PilaConEnteros.cpp
 * Author: cueva
 * 
 * Created on 22 de octubre de 2022, 07:28 AM
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include "PilaConEnteros.h"
using namespace std;

void *leenumero(ifstream &arch){
    int aux; // Podria ser double tambien
    arch >> aux;
    if (arch.eof()) return nullptr;
    return new int(aux);
}

double calculanumero(void *dato){
    // En este caso el peso es el mismo numero
    int *num = (int *)dato;
    return *num;
}

int cmpnumero(const void *izq, const void *der){
    void **camionIzq = (void **)izq;
    void **camionDer = (void **)der;
    void **pilaIzq = (void **)(*camionIzq);
    void **pilaDer = (void **)(*camionDer);
    double *pesoTotal1 = (double *)(pilaIzq[1]);
    double *pesoTotal2 = (double *)(pilaDer[1]);
    return (*pesoTotal2 - *pesoTotal1);
}

void imprimenumero(ofstream &arch, void *dato){
    int *num = (int *)dato;
    arch << *num << endl;
}

