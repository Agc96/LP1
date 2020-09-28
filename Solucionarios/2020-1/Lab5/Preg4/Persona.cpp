/* 
 * Archivo: Persona.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <cstring>
#include "Persona.h"

Persona::Persona() {
    inicializar();
}

Persona::Persona(const Persona& orig) {
    inicializar();
    *this = orig;
}

void Persona::inicializar() {
    nombre = nullptr;
    distrito = nullptr;
}

Persona::~Persona() {
    if (nombre) delete nombre;
    if (distrito) delete distrito;
}

/* Operadores sobrecargados */

Persona& Persona::operator =(const Persona& right) {
    // Verificar que el objeto de la derecha no sea este mismo objeto
    if (this == &right) return *this;
    // Copiar los datos del objeto de la derecha
    SetCodigo(right.codigo);
    SetDistrito(right.distrito);
    SetNombre(right.nombre);
    return *this;
}

/* Lectura e impresión de datos */

istream& Persona::leer(istream& in) {
    char buffer[MAX_LINEA], c;
    // Leer el nombre de la persona
    in.getline(buffer, MAX_LINEA, ',');
    SetNombre(buffer);
    // Leer el código de la persona
    in >> codigo >> c;
    // Leer el distrito de la persona
    in.getline(buffer, MAX_LINEA, ',');
    SetDistrito(buffer);
    return in;
}

ostream& Persona::imprimir(ostream& out) {
    out << "Codigo: " << codigo << endl;
    out << "Nombre: " << nombre << endl;
    out << "Distrito: " << distrito << endl;
    return out;
}

/* Encapsulamiento */

int Persona::GetCodigo() const {
    return codigo;
}

void Persona::SetCodigo(int codigo) {
    this->codigo = codigo;
}

char* Persona::GetDistrito() const {
    return crearCadena(distrito);
}

void Persona::SetDistrito(char* distrito) {
    if (this->distrito) delete this->distrito;
    this->distrito = crearCadena(distrito);
}

char* Persona::GetNombre() const {
    return crearCadena(nombre);
}

void Persona::SetNombre(char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = crearCadena(nombre);
}

/* Funciones auxiliares */

char* Persona::crearCadena(char* cadena) const {
    // Si cadena == nullptr, devolver nullptr
    if (!cadena) return nullptr;
    // Crear una nueva cadena y copiar los datos de la anterior
    char* copia = new char[strlen(cadena)+1];
    strcpy(copia, cadena);
    return copia;
}
