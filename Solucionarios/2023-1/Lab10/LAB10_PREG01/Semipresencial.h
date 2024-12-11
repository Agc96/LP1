/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:23 AM
 */

#ifndef SEMIPRESENCIAL_H
#define SEMIPRESENCIAL_H

#include <iostream>
#include <fstream>
#include "Alumno.h"
using namespace std;

class Semipresencial : public Alumno {
public:
    Semipresencial();
    Semipresencial(const Semipresencial& orig);
    virtual ~Semipresencial();
    // Encapsulamiento
    double GetDescuento() const;
    void SetDescuento(double descuento);
    double GetTotal() const;
    void SetTotal(double total);
    // Métodos
    void lee(ifstream &arch);
    void imprime(ofstream &arch);
private:
    double descuento;
    double total;
};

#endif /* SEMIPRESENCIAL_H */
