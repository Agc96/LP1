/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 20 de septiembre de 2019, 10:33 AM
 */

#include <iostream>
#include <fstream>
#include "funciones.h"
using namespace std;

int main() {
    // Abrir archivos
    ifstream registroTexto("files/registro.txt", ios::in);
    if (!registroTexto) {
        cout << "No se pudo abrir el registro de ventas en texto." << endl;
        exit(1);
    }
    ifstream devoluciones("files/devolucion.txt", ios::in);
    if (!devoluciones) {
        cout << "No se pudo abrir el archivo de devoluciones." << endl;
        exit(1);
    }
    ifstream precios("files/precios.txt", ios::in);
    if (!precios) {
        cout << "No se pudo abrir el archivo de devoluciones." << endl;
        exit(1);
    }
    ofstream reporte("files/reporte.txt", ios::out);
    if (!reporte) {
        cout << "No se pudo abrir el archivo del reporte." << endl;
        exit(1);
    }
    // Ejecutar pasos
    generarRegistroBinario(registroTexto);
    actualizarMontos(devoluciones, precios);
    generarReporte(reporte);
    cout << "Programa finalizado." << endl;
    return 0;
}
