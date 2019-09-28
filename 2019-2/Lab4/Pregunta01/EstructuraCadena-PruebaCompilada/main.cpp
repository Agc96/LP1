/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 06:34 PM
 */

#include <iostream>
#include "funciones.h"
using namespace std;

int main() {
    // Abrir archivos
    ifstream prueba("files/prueba.txt", ios::in);
    if (!prueba) {
        cerr << "No se pudo abrir el archivo prueba.txt." << endl;
        exit(1);
    }
    ofstream resultado("files/resultado.txt", ios::out);
    if (!resultado) {
        cerr << "No se pudo crear el archivo resultado.txt." << endl;
        exit(1);
    }
    // Realizar pruebas
    pruebaInicializacionLongitud(resultado);
    pruebaRecortarCadenas(resultado, prueba);
    pruebaIntercambiarCadenas(resultado, prueba);
    pruebaSobrecarga(resultado, prueba);
    return 0;
}
