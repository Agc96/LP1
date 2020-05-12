/* 
 * Archivo: lista.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:22 AM
 */

#include "funciones.h"

void crealista(void*& lista, void*(*funcionLeer)(ifstream&), int(*funcionComparar)(const void*, const void*)) {
    // Abrir archivo de entrada
    ifstream archivo("files/Stock.csv", ios::in);
    if (!archivo) {
        cerr << "No se pudo encontrar el archivo de stocks." << endl;
        exit(1);
    }
    // Generar un nodo para cada línea del archivo
    lista = NULL;
    while (true) {
        // Leer registro del archivo
        void* registro = funcionLeer(archivo);
        if (archivo.eof()) break;
        // Crear un nodo con el registro e insertarlo en la lista
        void** nodo = crearNodo(registro);
        if (lista == NULL) {
            // Colocar nodo como primer elemento de la lista
            lista = nodo;
        } else {
            // Insertar nodo de forma ordenada en la lista
            insertarNodoOrdenado(lista, nodo, funcionComparar);
        }
    }
}

void** crearNodo(void* registro) {
    void** nodo = new void*[2];
    nodo[0] = registro;
    nodo[1] = NULL;
    return nodo;
}

void insertarNodoOrdenado(void*& lista, void** nuevoNodo, int(*funcionComparar)(const void*, const void*)) {
    void **nodoActual = (void**)lista, ** nodoAnterior = NULL;
    // Recorrer la lista hasta que encontremos dónde insertar el nodo
    while (nodoActual != NULL) {
        if (funcionComparar(nodoActual[0], nuevoNodo[0]) > 0) {
            if (nodoAnterior == NULL) {
                // Insertar nuevo nodo como primer elemento de la lista
                nuevoNodo[1] = lista;
                lista = nuevoNodo;
            } else {
                // Añadir nuevo nodo entre los nodos anterior y actual
                nuevoNodo[1] = nodoActual;
                nodoAnterior[1] = nuevoNodo;
            }
            return;
        }
        nodoAnterior = nodoActual;
        nodoActual = (void**)(nodoActual[1]);
    }
    // Si no se encontró donde colocar, insertar al final
    nodoAnterior[1] = nuevoNodo;
}

void imprimelista(void* lista, void(*funcionImprimir)(ofstream&, void*)) {
    // Abrir archivo de salida
    ofstream archivo("files/Lista.txt", ios::out);
    if (!archivo) {
        cerr << "No se pudo generar el archivo de la lista generica." << endl;
        exit(1);
    }
    // Imprimir cada registro de la lista
    void** nodo = (void**)lista;
    while (nodo != NULL) {
        funcionImprimir(archivo, nodo[0]);
        nodo = (void**)(nodo[1]);
    }
}
