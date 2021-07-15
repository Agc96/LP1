/*
 * Archivo: ListaPacientes.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef LISTAPACIENTES_H
#define LISTAPACIENTES_H

#include <iostream>
#include "NodoPaciente.h"
using namespace std;

class ListaPacientes {
public:
    ListaPacientes();
    virtual ~ListaPacientes();
    // Métodos
    void creaLista(const char*);
    void imprimeLista(const char*);
private:
    class NodoPaciente* inicio;
    // Métodos auxiliares
    void agregarPaciente(class Paciente*);
    void imprimeCabeceraSeccion(ostream&, int);
    void imprimeCabeceraPacientes(ostream&, int);
    void imprimePacientes(ostream&, int);
    int contarSeguro();
    void separacion(ostream&, char);
};

#endif /* LISTAPACIENTES_H */
