/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:24 AM
 */

#ifndef BOLETA_H
#define BOLETA_H

#include <iostream>
#include <fstream>
#include "Alumno.h"
using namespace std;

#define NO_ENCONTRADO -1

class Boleta {
public:
    Boleta();
    Boleta(const Boleta& orig);
    virtual ~Boleta();
    // Métodos
    void leer(ifstream &, char tipo);
    int getCodigo();
    int getEscala();
    void actualizar(double);
    void imprimir(ofstream &);
private:
    Alumno *pboleta;
};

#endif /* BOLETA_H */
