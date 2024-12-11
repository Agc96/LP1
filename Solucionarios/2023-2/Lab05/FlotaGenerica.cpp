/* 
 * File:   FlotaGenerica.cpp
 * Author: cueva
 * 
 * Created on 23 de septiembre de 2023, 21:46
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "FlotaGenerica.h"
using namespace std;

enum NodoGenerico{SIG, DATO};

void cargacamiones(void *&flota, int num, double pesoMaximo,
					void*(*lee)(ifstream&), double(*calcula)(void*),
					const char *nomArch){
    void **lflota, *reg;
    int indice = 0;
    double peso, total = 0;
    ifstream arch(nomArch, ios::in);
    if (!arch) { // if (not arch.is_open())
    	cout << "No se encontro el archivo " << nomArch << endl; // cerr
    	exit(1);
    }
    // Inicializar flota
    lflota = new void*[num]{};
    for (int i = 0; i < num; i++) {
    	generapila(lflota[i]);
    }
    // Lectura de datos
    while(1){
        reg = lee(arch);
        if (reg == nullptr) break; // Fin de archivo
        peso = calcula(reg);
        if ((peso + total) > pesoMaximo){
            indice++; // Pasamos al siguiente camion
            total = 0; // Reiniciamos el total
            if (indice == num) break; // Si todos los camiones estan llenos, terminar la lectura
        }
        push(lflota[indice], reg, peso);
        total += peso;
    }
    flota = lflota;
}

void generapila(void*&pila){
    void **cabeza = new void*[2];
    cabeza[SIG] = nullptr;
    cabeza[DATO] = new double(0); // Peso
    pila = cabeza;
}

int pilavacia(void *pila){
    // Asumimos que la pila ya esta creada, solo verificar si tiene algun elemento
    void **cabeza = (void **)pila;
    return cabeza[SIG] == nullptr;
}

void push(void *&pila, void*dato, double peso){
    void **cabeza = (void**)pila;
    // Crear nuevo nodo
    void **nuevo = new void*[2];
    nuevo[SIG] = nullptr;
    nuevo[DATO] = dato;
    // Insertar como la cabeza de la pila
    if (!pilavacia(pila))
        nuevo[SIG] = cabeza[SIG];
    cabeza[SIG] = nuevo;
    // Actualizar peso total del camion
    double *pesoTotal = (double *)(cabeza[DATO]);
    (*pesoTotal) += peso;
}

// No es necesario
void *pop(void *&pila, double(*calcula)(void*)){
    // Verificamos si la pila esta vacia
    if (pilavacia(pila)) return nullptr;
    /// Actualizar pila
    void **cabeza=(void**)pila;
    void **aux = (void**)(cabeza[SIG]);
    void *dato = aux[DATO];
    cabeza[SIG] = aux[SIG];
    // aux[SIG] = nullptr;
    // Actualizar peso total
    double *pesoTotal = (double*) cabeza[DATO];
    (*pesoTotal) -= calcula(dato);
    return dato;
}

void  muestracamiones(void *flota,int num,void(*imprime)(ofstream&,void*),const char*nomarch){
    ofstream arch(nomarch,ios::out);
    if(!arch){
        cout <<"No se puede leer "<<nomarch;
        exit(1);
    }
    arch << fixed << setprecision(2);
    void **lflota=(void**)flota;
    for(int i=0; i<num;i++){
        void **pila = (void**)(lflota[i]);
        void **aux = (void**)(pila[SIG]);
        double *peso = (double*)(pila[DATO]);
        arch << "Camion " << right << setw(3) << (i+1) << setw(10) << ' ';
		arch << "Peso: " << setw(10) <<*peso<<endl;
        while(aux){
            imprime(arch,aux[DATO]);
            aux=(void**)(aux[SIG]);
        }
    }
}

