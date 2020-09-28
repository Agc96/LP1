/* 
 * Archivo: Alumno.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Persona.h"

class Alumno : public Persona {
public:
    Alumno();
    Alumno(const Alumno& orig);
    virtual ~Alumno();
    /* Encapsulamiento */
    int GetEscala() const;
    void SetEscala(int);
    void GetEspecialidad(char*) const;
    void SetEspecialidad(char*);
    void GetFacultad(char*) const;
    void SetFacultad(char*);
private:
    int escala;
    char* especialidad;
    char* facultad;
    void inicializar();
};

#endif /* ALUMNO_H */

