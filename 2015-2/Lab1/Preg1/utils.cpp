/*
 * File: utils.cpp
 * Author: Anthony Gutiérrez (20130095)
 */

#include <iostream>
#include <iomanip>
#include "utils.h"

#define TITULO MAX_LINEA/2
#define EMPLEADO (MAX_EMPLEADO+8)/2

using namespace std;

void repetir(char, int);

void separacion(char c, int numero) {
    repetir(c, numero);
    cout << endl;
}

void espacio(int numero) {
    repetir(' ', numero);
}

void repetir(char c, int numero) {
    for (int i = 0; i < numero; i++) {
        cout.put(c);
    }
}

void cabecera() {
    // Título
    espacio((MAX_LINEA-32)/2);
    cout << "REGISTRO DE LLAMADAS TELEFÓNICAS" << endl;
    // Separación
    separacion('=', MAX_LINEA);
    // Subtítulo del código
    espacio(1);
    cout << "CÓDIGO";
    espacio(3);
    // Subtítulo del empleado
    espacio((MAX_EMPLEADO-8)/2);
    cout << "EMPLEADO";
    espacio((MAX_EMPLEADO-8)/2 + 2);
    // Subtítulo del anexo
    cout << "ANEXO";
    espacio(2);
    // Subtítulo de la fecha
    espacio(3);
    cout << "FECHA";
    espacio(4);
    // Subtítulo de los tiempos
    cout << "TIEMPOS" << endl;
}
