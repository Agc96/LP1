/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:25 AM
 */

#include "Nodo.h"

Nodo::Nodo() {
    izq = der = nullptr;
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
    // La clase Arbol se encargará de gestionar la eliminación de memoria.
}
