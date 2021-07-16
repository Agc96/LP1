/*
 * Archivo: Falta.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#ifndef FALTA_H
#define FALTA_H

#include <iostream>
#include <fstream>
using namespace std;

class Falta {
public:
    Falta();
    Falta(int licencia, int fecha, const char* placa);
    virtual ~Falta();
    // Métodos
    void imprimir(ofstream& arch);
    // Encapsulamiento
    int GetFecha() const;
    void SetFecha(int fecha);
    int GetLicencia() const;
    void SetLicencia(int licencia);
    void GetPlaca(char* placa) const;
    void SetPlaca(const char* placa);
private:
    int licencia;
    int fecha;
    char* placa;
};

#endif /* FALTA_H */
