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

class Boleta {
public:
    Boleta();
    Boleta(const Boleta& orig);
    virtual ~Boleta();
    // Métodos
    void leer(ifstream &, char tipo);
    int comparar(const Boleta &otro);
    void imprimir(ofstream &);
private:
    Alumno *pboleta;
};

#endif /* BOLETA_H */
