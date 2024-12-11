/*
 * Archivo: BibliotecaPilaGenerica.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:09 PM
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BibliotecaPilaGenerica.h"
using namespace std;

#define MAX_BUFFER 50

enum Cabecera{NODO, CANT};
enum Nodo{SIG, DATO};

void cargaarreglo(void *&arreglo, int (*cmp)(const void*, const void*),
        void *(*lee)(ifstream&), const char *nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    void *dato, *buffer[MAX_BUFFER]{}, **arrexacto;
    int cant = 0;
    // Leer dato por dato
    while (true) {
        dato = lee(arch);
        if (dato == nullptr) break;
        buffer[cant++] = dato;
    }
    // Ordenar los datos de forma descendente
    qsort(buffer, cant, sizeof(void *), cmp);
    // Generar arreglo dinámico y exacto
    arrexacto = new void *[cant + 1];
    for (int i = 0; i <= cant; i++) arrexacto[i] = buffer[i];
    arreglo = arrexacto;
}

void cargapila(void *&pila, void *arreglo) {
    void **aux = (void **)arreglo;
    pila = creapila();
    // Agregar elementos del arreglo a la pila
    for (int i = 0; aux[i]; i++) {
        push(pila, aux[i]);
    }
}

void *creapila() {
    int *cant = new int;
    *cant = 0;
    void **pila = new void *[2];
    pila[SIG] = nullptr;
    pila[DATO] = cant;
    return pila;
}

void push(void *pila, void *dato) {
    void **cabecera, **nodo;
    // Obtener los punteros a la cabecera y al primer nodo de datos
    cabecera = (void **)pila;
    // Crear nodo para el dato
    nodo = new void *[2];
    nodo[SIG] = cabecera[NODO];
    nodo[DATO] = dato;
    // Hacer que la cabecera de la pila apunte al nuevo nodo de datos
    cabecera[NODO] = nodo;
    // Aumentar la cantidad de elementos
    int *cant = (int *)(cabecera[1]);
    (*cant)++;
}

void *pop(void *pila) {
    if (pilavacia(pila)) return nullptr;
    // Obtener los punteros a la cabecera y al primer nodo de datos
    void **cabecera, **nodo, *dato;
    cabecera = (void **)pila;
    nodo = (void **)(cabecera[NODO]);
    // Hacer que la cabecera de la pila apunte al siguiente nodo de datos
    cabecera[NODO] = nodo[SIG];
    dato = nodo[DATO];
    delete nodo;
    // Disminuir la cantidad de elementos
    int *cant = (int *)(cabecera[1]);
    (*cant)--;
    return dato;
}

bool pilavacia(void *pila) {
    return (pila == nullptr) || (cantelempila(pila) == 0);
}

int cantelempila(void *pila) {
    void **cabecera = (void **)pila;
    int *cant = (int *)(cabecera[CANT]);
    return *cant;
}

void muevepila(void *pilaini, void *&pilafin) {
    // Crear las pilas auxiliar y final
    void *pilaaux = creapila();
    pilafin = creapila();
    // Aplicar el algoritmo de Hanoi
    hanoi(cantelempila(pilaini), pilaini, pilaaux, pilafin);
}

void hanoi(int num, void *pilaini, void *pilaaux, void *pilafin) {
    void *dato;
    // Mover todos los discos menos el más grande (n) a la torre auxiliar
    if (num > 1) hanoi(num - 1, pilaini, pilafin, pilaaux);
    // Sacar disco n de la torre origen e insertarlo en la torre destino
    dato = pop(pilaini);
    push(pilafin, dato);
    // Mover todos los discos restantes encima del disco n
    if (num > 1) hanoi(num - 1, pilaaux, pilaini, pilafin);
}

void hanoi2(int num, void *pilaini, void *pilaaux, void *pilafin) {
    void *dato;
    if (num == 1) {
        dato = pop(pilaini);
        push(pilafin, dato);
    } else {
        hanoi(num - 1, pilaini, pilafin, pilaaux);
        dato = pop(pilaini);
        push(pilafin, dato);
        hanoi(num - 1, pilaaux, pilaini, pilafin);
    }
}

void imprimepila(void *pila, void (*imprime)(void *, ofstream &), const char *nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    void **cabecera = (void **)pila, **nodo = (void **)(cabecera[NODO]);
    for (int i = 0; nodo; i++) {
        imprime(nodo[DATO], arch);
        nodo = (void **)(nodo[SIG]);
    }
}
