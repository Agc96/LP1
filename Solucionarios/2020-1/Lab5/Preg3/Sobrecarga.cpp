/*
 * Archivo: Sobrecarga.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include "Sobrecarga.h"
using namespace std;

istream& operator >>(istream& in, class Aula& aula) {
    return aula.leer(in);
}

ostream& operator <<(ostream& out, class Aula& aula) {
    return aula.imprimir(out);
}
