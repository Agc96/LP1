/*
 * Archivo: Paciente.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
using namespace std;

class Paciente {
public:
    Paciente();
    Paciente(const Paciente& orig);
    virtual ~Paciente();
    // Métodos
    virtual int orden() = 0;
    virtual bool seguro() = 0;
    virtual istream& leer(istream&);
    virtual ostream& imprimir(ostream&);
    // Encapsulamiento
    int getCodMed() const;
    void setCodMed(int codMed);
    int getDni() const;
    void setDni(int dni);
    char* getNombre() const;
    void setNombre(char* nombre);
private:
    int dni;
    char* nombre;
    int codMed;
};

#endif /* PACIENTE_H */
