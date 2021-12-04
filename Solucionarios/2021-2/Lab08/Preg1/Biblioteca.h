/*
 * File:   Biblioteca.h
 * Author: Anthony Gutiérrez
 *
 * Created on 21 de noviembre de 2021, 05:43 PM
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <fstream>
#include "Copia.h"
using namespace std;

class Biblioteca {
public:
    Biblioteca();
    Biblioteca(const Biblioteca& orig);
    virtual ~Biblioteca();
    // Métodos
    void generaCopias();
    void actualizaLibros();
    void imprimeCopias();
private:
    Copia llibros[1000];
    // Métodos auxiliares
    int buscarCopia(const char*, int);
    void imprimirLinea(ofstream&);
    ifstream abrirArchivo(const char*);
    ofstream crearArchivo(const char*);
};

#endif /* BIBLIOTECA_H */
