/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 23 de septiembre de 2023, 21:19
 */

#include "FlotaGenerica.h"
#include "PilaConEnteros.h"
#include "PilaConRegistros.h"
using namespace std;

int main(int argc, char** argv) {
    int numcamiones;
    double pesomaximo;
    void *flota;
    

    numcamiones=5; pesomaximo=10;
    cargacamiones(flota,numcamiones,pesomaximo,leenumero,calculanumero,"numeros.txt");
    qsort(flota,numcamiones,sizeof(void*),cmpnumero);
    muestracamiones(flota,numcamiones,imprimenumero,"reportenum.txt");
    
    numcamiones=100; pesomaximo=400;
    cargacamiones(flota,numcamiones,pesomaximo,leeregistro,calcularegistro,"pedidos3.csv");
    qsort(flota,numcamiones,sizeof(void*),cmpregistro);
    muestracamiones(flota,numcamiones,imprimeregistro,"reporteregistro.txt");    
    

    return 0;
}

