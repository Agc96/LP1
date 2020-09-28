/* 
 * Archivo: Miembro.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef MIEMBRO_H
#define MIEMBRO_H

#include <iostream>
#include "Alumno.h"
#include "Profesor.h"
using namespace std;

class Miembro {
public:
    Miembro();
    Miembro(const Miembro& orig);
    virtual ~Miembro();
    /* Lectura e impresión */
    istream& leer(istream&); // También puede usarse ifstream
    ostream& imprimir(ostream&); // También puede usarse ofstream
    /* Manipulación de datos */
    const Alumno& GetAlumnoAt(int index);
    void SetAlumnoAt(int index, const Alumno& alumno);
    const Profesor& GetProfesorAt(int index);
    void SetProfesorAt(int index, const Profesor& alumno);
private:
    Alumno* lalumno;
    Profesor* lprofesor;
};

#endif /* MIEMBRO_H */
