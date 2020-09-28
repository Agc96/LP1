/* 
 * Archivo: Profesor.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "Profesor.h"

Profesor::Profesor() {
    inicializar();
}

Profesor::Profesor(const Profesor& orig) {
    inicializar();
    *this = orig;
}

void Profesor::inicializar() {
    categoria = nullptr;
    dedicacion = nullptr;
    seccion = nullptr;
    grado = nullptr;
}

Profesor::~Profesor() {
    if (categoria) delete categoria;
    if (dedicacion) delete dedicacion;
    if (seccion) delete seccion;
    if (grado) delete grado;
}

/* Operadores sobrecargados */

Profesor& Profesor::operator =(const Profesor& right) {
    // Verificar que el objeto de la derecha no sea este mismo objeto
    if (this == &right) return *this;
    // Copiar los datos del objeto de la derecha
    Persona::operator =(right);
    setCategoria(right.categoria);
    setDedicacion(right.dedicacion);
    setSeccion(right.seccion);
    setGrado(right.grado);
    return *this;
}

/* Lectura e impresión de datos */

istream& Profesor::leer(istream& in) {
    char buffer[MAX_LINEA];
    // Leer los datos principales (Persona)
    Persona::leer(in);
    // Leer la categoría del profesor
    in.getline(buffer, MAX_LINEA, ',');
    setCategoria(buffer);
    // Leer la dedicación del profesor
    in.getline(buffer, MAX_LINEA, ',');
    setDedicacion(buffer);
    // Leer la sección del profesor
    in.getline(buffer, MAX_LINEA, ',');
    setSeccion(buffer);
    // Leer el grado del profesor
    in.getline(buffer, MAX_LINEA);
    setGrado(buffer);
    return in;
}

ostream& Profesor::imprimir(ostream& out) {
    Persona::imprimir(out);
    out << "Categoria: " << categoria << endl;
    out << "Dedicacion: " << dedicacion << endl;
    out << "Seccion: " << seccion << endl;
    out << "Grado: " << grado << endl;
    return out;
}

/* Encapsulamiento */

char* Profesor::getCategoria() const {
    return crearCadena(categoria);
}

void Profesor::setCategoria(char* categoria) {
    if (this->categoria) delete this->categoria;
    this->categoria = crearCadena(categoria);
}

char* Profesor::getDedicacion() const {
    return crearCadena(dedicacion);
}

void Profesor::setDedicacion(char* dedicacion) {
    if (this->dedicacion) delete this->dedicacion;
    this->dedicacion = crearCadena(dedicacion);
}

char* Profesor::getGrado() const {
    return crearCadena(grado);
}

void Profesor::setGrado(char* grado) {
    if (this->grado) delete this->grado;
    this->grado = crearCadena(grado);
}

char* Profesor::getSeccion() const {
    return crearCadena(seccion);
}

void Profesor::setSeccion(char* seccion) {
    if (this->seccion) delete this->seccion;
    this->seccion = crearCadena(seccion);
}
