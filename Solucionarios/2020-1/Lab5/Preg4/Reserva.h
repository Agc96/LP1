/* 
 * Archivo: Reserva.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef RESERVA_H
#define RESERVA_H

#include <iostream>
#include <vector>
#include "Alumno.h"
#include "Profesor.h"
#include "PlCola.h"
#include "Aula.h"
using namespace std;

class Reserva {
public:
    void carga(const char*, const char*);
    void asigna(int);
    void imprime(const char*);
private:
    vector<Aula> vAula;
    PlCola<Alumno> alumnos;
    PlCola<Profesor> profesores;
    /* Métodos privados */
    void cargaAulas(istream&);
    void cargaMiembros(istream&);
    void separacion(ostream&, char, int);
};

#endif /* RESERVA_H */
