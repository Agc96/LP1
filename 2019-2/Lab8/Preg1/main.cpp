/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 12:55 PM
 */

#include "NumeroMuyGrande.h"
#include "Sobrecarga.h"
#include "Pruebas.h"
#include <iostream>
using namespace std;

int main() {
    // Apertura de archivos
    ifstream archEntrada("res/Entrada.txt", ios::in);
    if (!archEntrada) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        exit(1);
    }
    ofstream archSalida("res/Salida.txt", ios::out);
    if (!archSalida) {
        cerr << "No se pudo generar el archivo de salida." << endl;
        exit(1);
    }
    // Pruebas de números muy grandes
    pruebaInicializacion(archSalida);
    pruebaAsignacion(archSalida);
    pruebaOperaciones(archSalida);
    return 0;
}
