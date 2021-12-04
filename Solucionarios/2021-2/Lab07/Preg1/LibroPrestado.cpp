/*
 * File:   LibroPrestado.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 12 de noviembre de 2021, 09:17 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "FuncionesFecha.h"
#include "LibroPrestado.h"
using namespace std;

LibroPrestado::LibroPrestado() {
    codigoLib = nullptr;
    carne = 0;
    deuda = 0;
}

LibroPrestado::LibroPrestado(const LibroPrestado& orig) {
    codigoLib = nullptr;
    *this = orig;
}

LibroPrestado::~LibroPrestado() {
    if (codigoLib) delete codigoLib;
}

/* Métodos */

ifstream& LibroPrestado::leer(ifstream& arch) {
    char codigoLib[10], tipo, c;
    int carne, dd, mm, aaaa, fecha;
    // Leer los datos del archivo
    arch >> carne;
    if (arch.eof()) return arch;
    arch >> tipo >> c;
    arch.getline(codigoLib, 10, ',');
    arch >> dd >> c >> mm >> c >> aaaa;
    fecha = 10000*aaaa + 100*mm + dd;
    // Colocar los datos en el objeto
    setCarne(carne);
    setTipo(tipo);
    setCodigoLib(codigoLib);
    setFechaDeRetiro(fecha);
    return arch;
}

ofstream& LibroPrestado::imprimir(ofstream& arch) {
    char codigoLib[10];
    int fecha, dd, mm, aaaa;
    // Imprimir el código del libro
    getCodigoLib(codigoLib);
    arch << left << setw(15) << codigoLib;
    // Imprimir la fecha de retiro
    fecha = getFechaDeRetiro();
    aaaa = fecha / 10000;
    mm = (fecha % 10000) / 100;
    dd = fecha % 100;
    arch << right << setfill('0') << setw(2) << dd << '/';
    arch << setw(2) << mm << '/';
    arch << setw(4) << aaaa << setfill(' ');
    // Imprimir si tiene deuda o no
    if (getDeuda()) arch << setw(15) << "Deuda";
    arch << endl;
    return arch;
}

void LibroPrestado::calcularDeuda(int fecha) {
    int dias = numeroDeDias(getFechaDeRetiro(), fecha);
    switch (getTipo()) {
        case 'D':
            setDeuda(dias > 15);
            break;
        case 'E':
            setDeuda(dias > 10);
            break;
        case 'A':
            setDeuda(dias > 7);
            break;
    }
}

/* Sobrecargas */

void LibroPrestado::operator =(const LibroPrestado& orig) {
    char codigoLib[10];
    this->setCarne(orig.getCarne());
    this->setTipo(orig.getTipo());
    orig.getCodigoLib(codigoLib);
    this->setCodigoLib(codigoLib);
    this->setFechaDeRetiro(orig.getFechaDeRetiro());
    this->setDeuda(orig.getDeuda());
}

ifstream& operator >>(ifstream& arch, LibroPrestado& libPrest) {
    return libPrest.leer(arch);
}

ofstream& operator <<(ofstream& arch, LibroPrestado& libPrest) {
    return libPrest.imprimir(arch);
}

/* Encapsulamiento */

int LibroPrestado::getCarne() const {
    return carne;
}

void LibroPrestado::setCarne(int carne) {
    this->carne = carne;
}

void LibroPrestado::getCodigoLib(char *codigoLib) const {
    if (this->codigoLib) strcpy(codigoLib, this->codigoLib);
    else codigoLib[0] = 0;
}

void LibroPrestado::setCodigoLib(char *codigoLib) {
    if (this->codigoLib) delete this->codigoLib;
    this->codigoLib = new char[strlen(codigoLib)+1];
    strcpy(this->codigoLib, codigoLib);
}

int LibroPrestado::getDeuda() const {
    return deuda;
}

void LibroPrestado::setDeuda(int deuda) {
    this->deuda = deuda;
}

int LibroPrestado::getFechaDeRetiro() const {
    return fechaDeRetiro;
}

void LibroPrestado::setFechaDeRetiro(int fechaDeRetiro) {
    this->fechaDeRetiro = fechaDeRetiro;
}

char LibroPrestado::getTipo() const {
    return tipo;
}

void LibroPrestado::setTipo(char tipo) {
    this->tipo = tipo;
}
