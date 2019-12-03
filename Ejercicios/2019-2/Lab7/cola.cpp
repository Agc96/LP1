/* 
 * Archivo: cola.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:23 AM
 */

#include "funciones.h"

void encola(void*& cola, void* registro) {
    // Crear nodo e insertarlo en la cola
    void** nuevoNodo = crearNodo(registro);
    if (cola == NULL) {
        // Colocar nodo como primer elemento de la cola
        cola = nuevoNodo;
    } else {
        // Insertar nodo al final de la cola
        void** nodo = (void**)cola;
        while (nodo[1] != NULL) {
            nodo = (void**)(nodo[1]);
        }
        nodo[1] = nuevoNodo;
    }
}

void* desencola(void*& cola) {
    if (cola == NULL) return NULL;
    // Quitar primer nodo de la cola
    void** nodo = (void**)cola;
    cola = nodo[1];
    // Devolver el registro del nodo quitado
    return nodo[0];
}
