/*
 * Archivo: NodoPaciente.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef NODOPACIENTE_H
#define NODOPACIENTE_H

#include "ListaPacientes.h"
#include "Paciente.h"

class NodoPaciente {
public:
    NodoPaciente(class Paciente*);
    // NodoPaciente(const NodoPaciente& orig);
    virtual ~NodoPaciente();
    friend class ListaPacientes;
private:
    class Paciente* pac;
    class NodoPaciente* sig;
};

#endif /* NODOPACIENTE_H */
