/* 
 * Archivo: utilidades.cpp
 * Autor:   Anthony Gutiérrez <anthony.gutierrez@pucp.pe>
 * Código:  20130095
 * Creado el 13 de septiembre de 2019, 08:59 PM
 */

#include <fstream>
#include <iostream>
#include "utilidades.h"
using namespace std;

void separacion(ofstream& archivo, char c, int cantidad) {
    repetir(archivo, c, cantidad, true);
}

void espacios(ofstream& archivo, int cantidad) {
    repetir(archivo, ' ', cantidad, false);
}

void repetir(ofstream& archivo, char c, int cantidad, bool cambioLinea) {
    for (int i = 0; i < cantidad; i++) {
        archivo.put(c);
    }
    if (cambioLinea) {
        archivo << endl;
    }
}

double obtenerTipoCambio(ifstream& archivo, char moneda) {
    double tipoCambio = 1;
    archivo.seekg(0, ios::beg);
    while (true) {
        char c = archivo.get();
        if (archivo.eof()) break;
        // Verificar que es la moneda correcta
        if (c == moneda) {
            archivo >> tipoCambio;
            return tipoCambio;
        }
        // Ir a la siguiente línea
        while ((c = archivo.get()) != '\n');
    }
    cerr << "No se encontro el tipo de cambio para la moneda " << moneda;
    exit(1);
}
