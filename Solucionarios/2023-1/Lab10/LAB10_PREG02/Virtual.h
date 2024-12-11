/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:21 AM
 */

#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <iostream>
#include <fstream>
#include "Alumno.h"
using namespace std;

#define MAX_LIC_VIRTUAL 10
#define MONTO_VIRTUAL 100

class Virtual : public Alumno {
public:
    Virtual();
    Virtual(const Virtual& orig);
    virtual ~Virtual();
    // Encapsulamiento
    void GetLicencia(char *cad) const;
    void SetLicencia(const char *cad);
    double GetTotal() const;
    void SetTotal(double total);
    // Métodos
    void lee(ifstream &arch);
    void actualizatotal(double precio);
    void imprime(ofstream &arch);
private:
    char *licencia;
    double total;
};

#endif /* VIRTUAL_H */
