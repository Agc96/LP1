/* 
 * Archivo: Pruebas.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 01:08 PM
 */

#include "NumeroMuyGrande.h"
#define MAX_DIGITOS 20

void pruebaInicializacion(ofstream& archivo) {
    // Constructor vacío
    NumeroMuyGrande num1;
    archivo.width(MAX_DIGITOS);
    num1.imprimir(archivo);
    // Constructor con cadena
    NumeroMuyGrande num2("547382072206391");
    archivo.width(MAX_DIGITOS);
    num2.imprimir(archivo);
    // Constructor con objeto
    NumeroMuyGrande num3 = num2;
    archivo.width(MAX_DIGITOS);
    num3.imprimir(archivo);
}

void pruebaAsignacion(ofstream& archivo) {
    // TODO
}

void pruebaOperaciones(ofstream& archivo) {
    // TODO
}

void pruebaComparacion(ofstream& archivo) {
    // TODO
}

void pruebaOtros(ifstream& archEntrada, ofstream& archSalida) {
    // TODO
}
