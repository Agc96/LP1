/*
 * Archivo: NodoPaciente.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "NodoPaciente.h"

NodoPaciente::NodoPaciente(Paciente* pac) {
    this->pac = pac;
    this->sig = nullptr;
}

NodoPaciente::~NodoPaciente() {
    if (pac) delete pac;
    // ListaPaciente se encargará de eliminar el nodo siguiente.
}
