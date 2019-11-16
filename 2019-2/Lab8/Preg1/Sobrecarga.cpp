/* 
 * Archivo: Sobrecarga.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 01:10 PM
 */

#include "Sobrecarga.h"

ifstream& operator >> (ifstream& archivo, NumeroMuyGrande& numero) {
    return numero.leer(archivo);
}

ofstream& operator << (ofstream& archivo, NumeroMuyGrande& numero) {
    return numero.imprimir(archivo);
}
