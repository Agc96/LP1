/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include "Paciente.h"
#include "Medico.h"
using namespace std;

int main() {
    ifstream archPrueba("Prueba.txt", ios::in);
    if (!archPrueba) {
        cerr << "No se pudo abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    ofstream archRep("Reporte.txt", ios::out);
    if (!archRep) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    Medico medico;
    Paciente paciente;
    int dia, mes, anho;
    char c;
    // Leer los datos
    archPrueba >> medico;
    for (int i = 0; i < 4; i++) {
        archPrueba >> dia >> c >> mes >> c >> anho >> paciente;
        paciente.setFecha(10000*anho + 100*mes + dia);
        medico + paciente;
    }
    // Imprimir el reporte
    ++medico;
    archRep << medico;
    return 0;
}
