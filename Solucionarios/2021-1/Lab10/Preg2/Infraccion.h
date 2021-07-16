/*
 * Archivo: Infraccion.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:11 AM
 */

#ifndef INFRACCION_H
#define INFRACCION_H

#include <iostream>
#include <fstream>
using namespace std;

class Infraccion {
public:
    Infraccion();
    Infraccion(int codigo, const char* gravedad, double multa);
    virtual ~Infraccion();
    // Métodos
    virtual void imprimir(ofstream& arch) = 0;
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    void GetGravedad(char* gravedad);
    void SetGravedad(const char* gravedad);
    double GetMulta() const;
    void SetMulta(double multa);
private:
    int codigo;
    char* gravedad;
    double multa;
};

#endif /* INFRACCION_H */
