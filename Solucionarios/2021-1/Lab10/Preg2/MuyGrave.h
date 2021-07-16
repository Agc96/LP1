/*
 * Archivo: MuyGrave.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#ifndef MUYGRAVE_H
#define MUYGRAVE_H

#include <iostream>
#include <fstream>
#include "Infraccion.h"
using namespace std;

class MuyGrave: public Infraccion {
public:
    MuyGrave();
    MuyGrave(int codigo, const char* gravedad, double multa, int puntos, int meses);
    virtual ~MuyGrave();
    // Métodos
    void imprimir(ofstream& arch);
    // Encapsulamiento
    int GetMeses() const;
    void SetMeses(int meses);
    int GetPuntos() const;
    void SetPuntos(int puntos);
private:
    int puntos;
    int meses;
};

#endif /* MUYGRAVE_H */
