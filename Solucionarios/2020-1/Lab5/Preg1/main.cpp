/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include "Alumno.h"
#include "Profesor.h"
#include "Sobrecarga.h"
using namespace std;

int main() {
    char tipo, c;
    Alumno alumno;
    Profesor profesor;
    // Abrir el archivo
    ifstream arch("Prueba.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Prueba.csv." << endl;
        exit(1);
    }
    // Leer línea por línea
    while (true) {
        arch >> tipo >> c;
        if (arch.eof()) break;
        // Determinar el tipo de persona
        if (tipo == 'A') {
            arch >> alumno;
            cout << alumno << endl;
        } else if (tipo == 'P') {
            arch >> profesor;
            cout << profesor << endl;
        }
    }
    return 0;
}
