/* 
 * Archivo: Profesor.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PROFESOR_H
#define PROFESOR_H

#include "Persona.h"

class Profesor : public Persona {
public:
    Profesor();
    Profesor(const Profesor& orig);
    virtual ~Profesor();
private:
    char* categoria;
    char* dedicacion;
    char* seccion;
    char* grado;
};

#endif /* PROFESOR_H */
