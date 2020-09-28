/* 
 * Archivo: Profesor.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PROFESOR_H
#define PROFESOR_H

#include <iostream>
#include "Persona.h"
using namespace std;

class Profesor: public Persona {
public:
    Profesor();
    Profesor(const Profesor&);
    virtual ~Profesor();
    /* Operadores sobrecargados */

    Profesor& operator =(const Profesor&);
    /* Lectura e impresión de datos */
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    /* Encapsulamiento */
    char* getCategoria() const;
    void setCategoria(char*);
    char* getDedicacion() const;
    void setDedicacion(char*);
    char* getGrado() const;
    void setGrado(char*);
    char* getSeccion() const;
    void setSeccion(char*);
private:
    char* categoria;
    char* dedicacion;
    char* seccion;
    char* grado;
    void inicializar();
};

#endif /* PROFESOR_H */
