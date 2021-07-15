/*
 * Archivo: Paciente.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <cstring>
#include "Paciente.h"
using namespace std;

#define MAX_BUFFER 100

Paciente::Paciente() {
    nombre = nullptr;
}

Paciente::Paciente(const Paciente& orig) {
    nombre = nullptr;
    *this = orig;
}

Paciente::~Paciente() {
    if (nombre) delete nombre;
}

/* Métodos y sobrecargas de la clase */

istream& Paciente::leer(istream& in) {
    char buffer[MAX_BUFFER];
    // Leer el estado del paciente
    in >> ws >> estado;
    if (in.eof()) return in;
    // Leer el código del paciente
    in >> codigo;
    // Leer el nombre del paciente
    in >> buffer;
    setNombre(buffer);
    // Leer la prima del paciente
    in >> prima;
    return in;
}

Paciente& Paciente::operator =(const Paciente& orig) {
    setFecha(orig.fecha);
    setCodigo(orig.codigo);
    setNombre(orig.nombre);
    setPrima(orig.prima);
    setEstado(orig.estado);
    return *this;
}

/* Encapsulamiento */

int Paciente::getCodigo() const {
    return codigo;
}

void Paciente::setCodigo(int codigo) {
    this->codigo = codigo;
}

char Paciente::getEstado() const {
    return estado;
}

void Paciente::setEstado(char estado) {
    this->estado = estado;
}

int Paciente::getFecha() const {
    return fecha;
}

void Paciente::setFecha(int fecha) {
    this->fecha = fecha;
}

char* Paciente::getNombre() {
    return crearCadena(nombre);
}

void Paciente::setNombre(char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = crearCadena(nombre);
}

double Paciente::getPrima() const {
    return prima;
}

void Paciente::setPrima(double prima) {
    this->prima = prima;
}

/* Métodos auxiliares */

char* Paciente::crearCadena(char *buffer) {
    if (buffer == nullptr) return nullptr;
    char* cad = new char[strlen(buffer)+1];
    strcpy(cad, buffer);
    return cad;
}

/* Sobrecarga de lectura */

istream& operator >>(istream& in, Paciente& paciente) {
    return paciente.leer(in);
}
