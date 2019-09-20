/* 
 * Archivo: utilidades.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 20 de septiembre de 2019, 10:38 AM
 */

#include <fstream>
#include "constantes.h"
#include "utilidades.h"
using namespace std;

void separacion(ofstream& archivo, char c) {
    repetir(archivo, c, MAX_LINEA, true);
}

void espacios(ofstream& archivo, int cantidad) {
    repetir(archivo, ' ', cantidad, false);
}

void repetir(ofstream& archivo, char c, int cantidad, bool agregarCambioLinea) {
    for (int i = 0; i < cantidad; i++) {
        archivo.put(c);
    }
    if (agregarCambioLinea) {
        archivo << endl;
    }
}
