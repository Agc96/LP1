/* 
 * Archivo: utilidades.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 19 de septiembre de 2019, 05:46 PM
 */

#include <iostream>
#include "utilidades.h"
using namespace std;

void separacion(char c, int longitud) {
    repetir(c, longitud, true);
}

void espacios(int longitud) {
    repetir(' ', longitud, false);
}

void repetir(char c, int longitud, bool cambioLinea) {
    for (int i = 0; i < longitud; i++) {
        cout.put(c);
    }
    if (cambioLinea) {
        cout << endl;
    }
}
