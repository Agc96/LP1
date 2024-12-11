/* 
 * File:   PilaConRegistros.cpp
 * Author: cueva
 * 
 * Created on 22 de octubre de 2022, 10:53 PM
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "PilaConRegistros.h"

using namespace std;

/*
JXD-139,50375303,6,120
CRU-009,50375303,5,200
YYK-309,22777006,3,165
 */

enum IndicesRegistro{COD_PROD, DNI_CLI, CANT, PESO};

void* leeregistro(ifstream &arch){
    int dni, cant;
    char *codProd, buffer[10], coma;
    double peso;
    // Lectura de datos
    arch.getline(buffer,10,',');
    if(arch.eof()) return nullptr;
    arch >> dni >> coma >> cant >> coma >> peso >> ws;
    // Realizar cadena dinamica y exacta
    codProd = new char[strlen(buffer)+1];
    strcpy(codProd, buffer);
    // Crear registro generico
    void **registro = new void*[4];
    registro[COD_PROD] = codProd;
    registro[DNI_CLI] = new int(dni);
    registro[CANT] = new int(cant);
    registro[PESO] = new double(peso);
    return registro;
}

int cmpregistro(const void *izq, const void *der){
    void **camionIzq = (void **)izq;
    void **camionDer = (void **)der;
    void **pilaIzq = (void **)(*camionIzq);
    void **pilaDer = (void **)(*camionDer);
    double *pesoTotal1 = (double *)(pilaIzq[1]);
    double *pesoTotal2 = (double *)(pilaDer[1]);
    return ((*pesoTotal2)*100 - (*pesoTotal1)*100);
}

void imprimeregistro(ofstream &arch,void* dato){
    void **aux = (void**)dato;
    char *cad = (char*)aux[COD_PROD];
    int *codigo = (int*)aux[DNI_CLI];
    int *cant = (int*)aux[CANT];
    double *peso = (double*)aux[PESO];
    arch <<setw(20)<<cad<<setw(10)<<*cant<<setprecision(2)<< fixed<<setw(10)<<*peso<<endl;
}

double calcularegistro(void *dato){
    void **reg = (void**)dato;
    double *num = (double*)(reg[PESO]);
    return *num;
}
