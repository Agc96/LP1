/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 26 de septiembre de 2019, 05:41 PM
 */

#include <iostream>
#include "cadena.h"
using namespace std;

int main(int argc, char** argv) {
    Cadena cadena;
    inicializa(cadena);
    /* // Versión inicial
    cout << "Probando versión inicial" << endl;
    leer(cadena, '#');
    imprimir(cadena);
    leer(cadena);
    imprimir(cadena);
    // Versión con sobrecarga
    cout << "Probando versión con sobrecarga" << endl;
    cin >> cadena;
    cout << cadena; */
    // Recortar
    cout << "Probando recortar" << endl;
    leer(cadena, '#');
    recortar(cadena);
    // cout << cadena;
    imprimir(cadena);
    return 0;
}
