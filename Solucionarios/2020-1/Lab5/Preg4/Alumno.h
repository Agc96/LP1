/* 
 * Archivo: Alumno.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include "Persona.h"
using namespace std;

class Alumno: public Persona {
public:
    Alumno();
    Alumno(const Alumno&);
    virtual ~Alumno();
    /* Operadores sobrecargados */
    Alumno& operator =(const Alumno&);
    /* Lectura y escritura */
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    /* Encapsulamiento */
    int GetEscala() const;
    void SetEscala(int);
    char* GetEspecialidad() const;
    void SetEspecialidad(char*);
    char* GetFacultad() const;
    void SetFacultad(char*);
private:
    int escala;
    char* especialidad;
    char* facultad;
    void inicializar();
};

#endif /* ALUMNO_H */
