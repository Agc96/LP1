/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:10 AM
 */

#include <iostream>
#include <fstream>
#include "ListaNotas.h"
using namespace std;

int main() {
    // Apertura de archivos
    ifstream entrada("Cursos.csv", ios::in);
    if (!entrada) {
        cerr << "No se pudo encontrar el archivo de notas." << endl;
        exit(1);
    }
    ofstream salida("Notas.txt", ios::out);
    if (!salida) {
        cerr << "No se pudo generar el archivo de salida." << endl;
        exit(1);
    }
    // Leer notas e imprimir resultados
    ListaNotas lista;
    lista.leer(entrada);
    lista.imprimir(salida);
    return 0;
}
