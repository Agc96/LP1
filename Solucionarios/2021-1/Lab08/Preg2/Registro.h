/*
 * Archivo: Registro.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:53 AM
 */

#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include "Conductor.h"
#include "Leve.h"
#include "Grave.h"
#include "MuyGrave.h"
using namespace std;

class Registro : public Conductor {
public:
    Registro(); // No es necesario usar un constructor copia
    virtual ~Registro();
    // Métodos principales
    void guardarFalta(int, int, const char*);
    void guardarInfraccion(int, const char*, double, double, int, int);
    void imprimirFalta(ofstream&);
    void actualizarEstadisticas(double&, int&, int&);
private:
    Leve lleve;
    Grave lgrave;
    MuyGrave lmgrave;
    // Métodos auxiliares
    ifstream abrirArchivo(const char*);
    void imprimirDatosFalta(ofstream&, int, char*);
};

#endif /* REGISTRO_H */
