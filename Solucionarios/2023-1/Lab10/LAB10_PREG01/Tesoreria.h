/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:30 AM
 */

#ifndef TESORERIA_H
#define TESORERIA_H

#include <iostream>
#include <fstream>
#include "Arbol.h"
using namespace std;

class Tesoreria {
public:
    Tesoreria();
    Tesoreria(const Tesoreria& orig);
    virtual ~Tesoreria();
    // Métodos
    void cargaalumnos();
    void imprimeboleta();
private:
    Arbol aboleta;
    // Métodos auxiliares
    void abrirArchivoEntrada(ifstream &, const char *);
    void abrirArchivoSalida(ofstream &, const char *);
    void imprimirLinea(ofstream &, char);
};

#endif /* TESORERIA_H */
