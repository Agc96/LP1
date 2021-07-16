/*
 * Archivo: Grave.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#ifndef GRAVE_H
#define GRAVE_H

#include <iostream>
#include <fstream>
#include "Infraccion.h"
using namespace std;

class Grave: public Infraccion {
public:
    Grave();
    Grave(int codigo, const char* gravedad, double multa, double descuento, int puntos);
    virtual ~Grave();
    // Métodos
    void imprimir(ofstream& arch);
    // Encapsulamiento
    double GetDescuento() const;
    void SetDescuento(double descuento);
    int GetPuntos() const;
    void SetPuntos(int puntos);
private:
    double descuento;
    int puntos;
};

#endif /* GRAVE_H */
