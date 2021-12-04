/*
 * File:   Copia.h
 * Author: Anthony Gutiérrez
 *
 * Created on 21 de noviembre de 2021, 05:49 PM
 */

#ifndef COPIA_H
#define COPIA_H

#include <iostream>
#include <fstream>
#include "Disponible.h"
#include "Libro.h"
#include "Perdida.h"
#include "Prestamo.h"
using namespace std;

class Copia : public Libro {
public:
    Copia();
    Copia(const Copia& orig);
    virtual ~Copia();
    // Métodos
    void leer(ifstream& arch);
    void copiar(const Copia& orig);
    void actualizar(int hoy, int fecha);
    void imprimir(ofstream& arch, bool lineaInicial);
    // Encapsulamiento
    void GetEstado(char* estado) const;
    void SetEstado(const char* estado);
    int GetNumero() const;
    void SetNumero(int numero);
private:
    int numero;
    char* estado;
    Disponible Odisponible;
    Prestamo Oprestamo;
    Perdida Operdida;
};

#endif /* COPIA_H */
