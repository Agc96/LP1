/*
 * File:   main.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:32 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Cliente.h"
#include "Producto.h"
#include "Pedido.h"
using namespace std;

int main(int argc, char** argv) {
    ifstream archPrueba("Prueba.txt", ios::in);
    if (!archPrueba) {
        cerr << "No se pudo abrir el archivo de prueba" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo crear el archivo del reporte" << endl;
        exit(1);
    }
    Cliente cliente;
    Producto producto;
    Pedido pedido;
    archPrueba >> cliente;
    archPrueba >> producto;
    archReporte << fixed << setprecision(2);
    archReporte << cliente;  archReporte << endl;
    archReporte << producto; archReporte << endl;
    for (int i = 0; i < 2; i++) {
        archPrueba >> pedido;
        producto += pedido;
    }
    cliente += pedido;
    archReporte << cliente;  archReporte << endl;
    archReporte << producto;
    return 0;
}
