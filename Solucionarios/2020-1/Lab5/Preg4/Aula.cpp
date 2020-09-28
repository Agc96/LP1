/* 
 * Archivo: Aula.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <cstring>
#include "Aula.h"

#define MAX_LINEA 120

Aula::Aula() {
    inicializar();
}

Aula::Aula(const Aula& orig) {
    inicializar();
    *this = orig;
}

Aula::~Aula() {
    if (clave) delete clave;
    if (nombre) delete nombre;
}

void Aula::inicializar() {
    clave = nullptr;
    capacidad = 0;
    codigo = 0;
    nombre = nullptr;
    tipo = 'S';
}

/* Operadores sobrecargados */

Aula& Aula::operator =(const Aula& right) {
    // Verificar que el objeto de la derecha no sea este mismo objeto
    if (this == &right) return *this;
    // Copiar los datos del objeto de la derecha
    setClave(right.clave);
    setCapacidad(right.capacidad);
    setCodigo(right.codigo);
    setNombre(right.nombre);
    setTipo(right.tipo);
    return *this;
}

/* Lectura e impresión de datos */

istream& Aula::leer(istream& in) {
    char buffer[MAX_LINEA];
    in >> ws;
    // Leer la clave del aula
    in.getline(buffer, MAX_LINEA, ',');
    setClave(buffer);
    // Leer la capacidad del aula
    in >> capacidad;
    return in;
}

ostream& Aula::imprimir(ostream& out) {
    out << "Aula: " << clave << endl;
    out << "Capacidad: " << capacidad << endl;
    out << "Codigo: " << codigo << endl;
    if (nombre) out << "Nombre: " << nombre << endl;
    else out << "Nombre: (Sin Asignar)" << endl;
    out << "Tipo: " << tipo << endl;
    return out;
}

/* Encapsulamiento */

char* Aula::getClave() const {
    return crearCadena(clave);
}

void Aula::setClave(char* clave) {
    if (this->clave) delete this->clave;
    this->clave = crearCadena(clave);
}

int Aula::getCapacidad() const {
    return capacidad;
}

void Aula::setCapacidad(int capacidad) {
    this->capacidad = capacidad;
}

int Aula::getCodigo() const {
    return codigo;
}

void Aula::setCodigo(int codigo) {
    this->codigo = codigo;
}

char* Aula::getNombre() const {
    return crearCadena(nombre);
}

void Aula::setNombre(char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = crearCadena(nombre);
}

char Aula::getTipo() const {
    return tipo;
}

void Aula::setTipo(char tipo) {
    this->tipo = tipo;
}

/* Funciones auxiliares */

char* Aula::crearCadena(char* cadena) const {
    // Si cadena == nullptr, devolver nullptr
    if (!cadena) return nullptr;
    // Crear una nueva cadena y copiar los datos de la anterior
    char* copia = new char[strlen(cadena)+1];
    strcpy(copia, cadena);
    return copia;
}
