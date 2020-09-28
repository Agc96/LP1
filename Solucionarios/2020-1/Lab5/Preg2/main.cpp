/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include "PlCola.h"
#include "Sobrecarga.h"
using namespace std;

int main() {
    PlCola<Alumno> cola;
    Alumno dato;
    // Abrir el archivo
    ifstream archPrueba("Prueba.csv", ios::in);
    if (!archPrueba) {
        cerr << "No se pudo abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    // Leer los números
    while (true) {
        archPrueba >> dato;
        if (archPrueba.eof()) break;
        cola.encolar(dato);
    }
    // Imprimir los números en un archivo
    ofstream archReporte("Reporte.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    cola.imprimir(archReporte);
    // Desencolar los números
    while (!cola.estaVacia()) {
        dato = cola.desencolar();
        cout << dato << endl;
    }
    return 0;
}
