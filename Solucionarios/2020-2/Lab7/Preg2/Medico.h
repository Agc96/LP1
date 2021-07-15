/*
 * Archivo: Medico.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include "Paciente.h"
using namespace std;

#define MAX_PACIENTES 100

class Medico {
public:
    Medico();
    Medico(const Medico&);
    virtual ~Medico();
    // Métodos de la clase
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    // Sobrecargas de la clase
    Medico& operator =(const Medico&);
    void operator +(Paciente&);
    void operator *(int);
    void operator -(int);
    void operator ++();
    // Encapsulamiento
    char* getCodigo();
    void setCodigo(char* codigo);
    char* getEspecialidad();
    void setEspecialidad(char* especialidad);
    char* getNombre() const;
    void setNombre(char* nombre);
    double getTarifa() const;
    void setTarifa(double tarifa);
private:
    char* codigo;
    char* nombre;
    char* especialidad;
    double tarifa;
    int fechas[MAX_PACIENTES];
    int pacientes[MAX_PACIENTES];
    double prima[MAX_PACIENTES];
    char estado[MAX_PACIENTES];
    int numPac;
    double ingresosP;
    double ingresosS;
    // Métodos auxiliares
    void inicializar();
    char* crearCadena(char*);
    void imprimirContador(ostream&, int);
    void imprimirFecha(ostream&, int);
    void imprimirPacientes(ostream&, char);
    void separacion(ostream&, char);
};

// Sobrecargas de lectura e impresión
istream& operator >>(istream&, Medico&);
ostream& operator <<(ostream&, Medico&);

#endif /* MEDICO_H */
