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

void cabecera(int inicioDia, int inicioMes, int inicioAnho, int finDia,
        int finMes, int finAnho) {
    // Título
    espacio((MAX_LINEA-70)/2);
    cout << "REGISTRO DE LLAMADAS TELEFÓNICAS entre la fecha ";
    cout << setfill('0') << setw(2) << inicioDia << '/';
    cout << setw(2) << inicioMes << '/' << setw(4) << inicioAnho << " y ";
    cout << setw(2) << finDia << '/' << setw(2) << finMes << '/';
    cout << setw(4) << finAnho << endl;
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

void imprimirHora(double totalSegundos, bool cambioLinea) {
    int horas = totalSegundos / 3600;
    int minutos = (totalSegundos - 3600*horas) / 60;
    int segundos = (totalSegundos - 3600*horas - 60*minutos);
    cout << " (" << horas << "h " << minutos << "min " << segundos << "s)";
    if (cambioLinea) {
        cout << endl;
    }
}

void imprimirFecha(int dia, int mes, int anho, bool cambioLinea) {
    cout << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/';
    cout << setw(4) << anho;
    if (cambioLinea) {
        cout << endl;
    }
}
