/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:20 AM
 */

#ifndef PRESENCIAL_H
#define PRESENCIAL_H

#include <iostream>
#include <fstream>
#include "Alumno.h"
using namespace std;

class Presencial : public Alumno {
public:
    Presencial();
    Presencial(const Presencial& orig);
    virtual ~Presencial();
    // Encapsulamiento
    double GetRecargo() const;
    void SetRecargo(double recargo);
    double GetTotal() const;
    void SetTotal(double total);
    // Métodos
    void lee(ifstream &arch);
    void imprime(ofstream &arch);
private:
    double recargo;
    double total;
};

#endif /* PRESENCIAL_H */
