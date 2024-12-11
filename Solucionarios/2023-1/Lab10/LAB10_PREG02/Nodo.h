/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:25 AM
 */

#ifndef NODO_H
#define NODO_H

#include "Boleta.h"

class Nodo {
public:
    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    friend class Arbol;
private:
    Boleta dboleta;
    Nodo *izq;
    Nodo *der;
};

#endif /* NODO_H */
