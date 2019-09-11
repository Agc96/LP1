/*
 * Autor:   Anthony Gutiérrez
 * Código:  20103095
 */

#include <iostream>
#include "constants.h"
#include "utilities.h"

using namespace std;

void repetir(char c, int cantidad, bool cambioLinea) {
    for (int i = 0; i < cantidad; i++) {
        cout.put(c);
    }
    if (cambioLinea) {
        cout << endl;
    }
}

void separacion(char c) {
    repetir(c, MAX_LINEA, true);
}

void espacios(int cantidad) {
    repetir(' ', cantidad, false);
}

void imprimirMoneda(char moneda) {
    switch (moneda) {
        case 'S':
            cout << "SOLES";
            break;
        case '$':
            cout << "DOLARES";
            break;
        case '&':
            cout << "EUROS";
            break;
    }
}
