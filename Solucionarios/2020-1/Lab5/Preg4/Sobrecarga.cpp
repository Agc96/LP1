/* 
 * Archivo: Sobrecarga.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include "Sobrecarga.h"
using namespace std;

istream& operator >>(istream& in, class Persona& persona) {
    return persona.leer(in);
}

ostream& operator <<(ostream& out, class Persona& persona) {
    return persona.imprimir(out);
}

istream& operator >>(istream& in, class Alumno& alumno) {
    return alumno.leer(in);
}

ostream& operator <<(ostream& out, class Alumno& alumno) {
    return alumno.imprimir(out);
}

istream& operator >>(istream& in, class Profesor& profesor) {
    return profesor.leer(in);
}

ostream& operator <<(ostream& out, class Profesor& profesor) {
    return profesor.imprimir(out);
}

istream& operator >>(istream& in, class Aula& aula) {
    return aula.leer(in);
}

ostream& operator <<(ostream& out, class Aula& aula) {
    return aula.imprimir(out);
}
