/* 
 * Archivo: PlCola.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PLCOLA_H
#define PLCOLA_H

#include <iostream>
#include "PlNodo.h"
using namespace std;

template <typename T> class PlCola {
public:
    PlCola();
    virtual ~PlCola();
    /* Métodos de la cola */
    void encolar(const T&);
    T desencolar();
    bool estaVacia();
    void imprimir(ostream&);
private:
    class PlNodo<T>* inicio;
    class PlNodo<T>* fin;
};

template <typename T> PlCola<T>::PlCola() {
    inicio = nullptr;
    fin = nullptr;
}

template <typename T> PlCola<T>::~PlCola() {
    class PlNodo<T>* aux;
    // Limpiar los nodos
    while (inicio) {
        aux = inicio;
        inicio = inicio->sig;
        delete aux;
    }
}

template <typename T> void PlCola<T>::encolar(const T& dato) {
    // Crear el nuevo nodo con el dato
    class PlNodo<T>* nuevo = new PlNodo<T>();
    nuevo->dato = dato;
    // Actualizar el puntero al último nodo de la cola
    if (fin) fin->sig = nuevo;
    else inicio = nuevo;
    // Actualizar el final de la cola
    fin = nuevo;
}

template <typename T> T PlCola<T>::desencolar() {
    T dato;
    // Verificar que haya algún dato en la cola
    if (inicio) {
        dato = inicio->dato;
        // Limpiar el nodo del principio de la cola
        class PlNodo<T>* aux = inicio;
        inicio = inicio->sig;
        delete aux;
        // Actualizar el final de la cola si es necesario
        if (!inicio) fin = nullptr;
    }
    return dato;
}

template <typename T> bool PlCola<T>::estaVacia() {
    return inicio == nullptr || fin == nullptr;
}

template <typename T> void PlCola<T>::imprimir(ostream& out) {
    class PlNodo<T>* aux = inicio;
    while (aux) {
        out << aux->dato << endl;
        aux = aux->sig;
    }
}

#endif /* PLCOLA_H */
