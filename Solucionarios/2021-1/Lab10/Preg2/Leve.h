/*
 * Archivo: Leve.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#ifndef LEVE_H
#define LEVE_H

#include <iostream>
#include <fstream>
#include "Infraccion.h"
using namespace std;

class Leve: public Infraccion {
public:
    Leve();
    Leve(int codigo, const char* gravedad, double multa, double descuento);
    virtual ~Leve();
    // Métodos
    void imprimir(ofstream& arch);
    // Encapsulamiento
    double GetDescuento() const;
    void SetDescuento(double descuento);
private:
    double descuento;
};

#endif /* LEVE_H */
