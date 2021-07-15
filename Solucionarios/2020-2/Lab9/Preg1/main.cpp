/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de diciembre de 2020, 09:32 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Paciente.h"
#include "Ambulatorio.h"
#include "Urgencia.h"
#include "Emergencia.h"
using namespace std;

int main() {
    ifstream arch("Prueba.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    ofstream rep("Reporte.txt", ios::out);
    if (!rep) {
        cerr << "No se pudo generar el archivo Reporte.txt" << endl;
        exit(1);
    }
    // Leer un paciente ambulatorio
    Paciente* pac = new Ambulatorio();
    pac->leer(arch);
    pac->imprimir(rep);
    delete pac;
    // Leer un paciente de urgencia
    pac = new Urgencia();
    pac->leer(arch);
    pac->imprimir(rep);
    delete pac;
    // Leer un paciente de emergencia
    pac = new Emergencia();
    pac->leer(arch);
    pac->imprimir(rep);
    delete pac;
    return 0;
}
