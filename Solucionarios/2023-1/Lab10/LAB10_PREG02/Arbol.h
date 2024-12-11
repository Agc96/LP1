/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:27 AM
 */

#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include <fstream>
#include "Escala.h"
#include "Nodo.h"
using namespace std;

class Arbol {
public:
    Arbol();
    Arbol(const Arbol& orig);
    virtual ~Arbol();
    // Métodos
    void insertarAlumno(ifstream &arch, char tipo);
    void insertarEscala(ifstream &arch, int escala);
    void actualizarTotales();
    void imprimir(ofstream &arch);
private:
    Nodo *raiz;
    Escala lescala[5];
    // Métodos auxiliares
    void insertarRecursivo(Nodo *nodo, Nodo *nuevo);
    void actualizarRecursivo(Nodo *nodo);
    void imprimirRecursivo(ofstream &arch, Nodo *nodo);
    void eliminarRecursivo(Nodo *nodo);
};

#endif /* ARBOL_H */
