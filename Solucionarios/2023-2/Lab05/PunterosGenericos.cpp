/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PunterosGenericos.cpp
 * Author: cueva
 * 
 * Created on 23 de septiembre de 2023, 21:37
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include "PunterosGenericos.h"

using namespace std;

/*
PPX-620,Aire acondicionado tipo split,5
ISU-815,Audifonos,0.5
ARS-231,Audifonos Stereos,0.6
*/


void *leeproductos(ifstream &arch){
    char cadena[200],*codigo,*nombre,c,cod[10];
    double *peso;
    void **registro;
    
    arch.getline(cod,10,',');
    if(arch.eof()) return NULL;
    codigo = new char[strlen(cod)+1];
    strcpy(codigo,cod);
    arch.getline(cadena,200,',');
    nombre = new char[strlen(cadena)+1];
    strcpy(nombre,cadena);
    peso = new double;
    arch >> *peso;
    arch.get();
    
    registro = new void*[3];
    registro[0] = codigo;
    registro[1] = nombre;
    registro[2] = peso;
    
    return registro;
    
}

void cargaproductos(void *&productos){
    int i=0;
    void *buff[500],**lproductos;
    
    ifstream arch("productos3.csv",ios::in);
    if(!arch){
        cout <<"No se puede leer Productos";
        exit(1);
    }
    while(1){
        buff[i] = leeproductos(arch);
        if(!buff[i]) break;
        i++;
    }
    lproductos = new void*[i+1];
    for(int j=0;j<=i;j++){
        lproductos[j] = buff[j]; 
    }
    productos = lproductos;
    //imprimeproductos(productos);
}