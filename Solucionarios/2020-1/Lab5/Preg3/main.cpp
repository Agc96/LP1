/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "Aula.h"
#include "Sobrecarga.h"
using namespace std;

int main() {
    vector<Aula> vAula;
    Aula aula;
    // Leer las aulas línea por línea
    ifstream archAulas("Aulas.csv", ios::in);
    if (!archAulas) {
        cerr << "No se pudo abrir el archivo Aulas.csv" << endl;
        exit(1);
    }
    while (true) {
        archAulas >> aula;
        if (archAulas.eof()) break;
        vAula.push_back(aula);
    }
    // Imprimir las aulas
    ofstream archReporte("Reporte.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    for (vector<Aula>::iterator it = vAula.begin(); it != vAula.end(); ++it) {
        archReporte << *it << endl;
    }
    return 0;
}
