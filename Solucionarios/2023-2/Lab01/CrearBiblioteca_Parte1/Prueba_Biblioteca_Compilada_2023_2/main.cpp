/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 06:36 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Sobrecargas.h"
#include "AperturaDeArchivos.h"
using namespace std;

int main() {
    ifstream archPrueba;
    ofstream archReporte;
    struct Cliente clientes[3];
    struct Producto productos[5];
    struct Pedido pedido;
    AperturaDeUnArchivoDeTextosParaLeer(archPrueba, "Prueba.txt");
    AperturaDeUnArchivoDeTextosParaEscribir(archReporte, "Reporte.txt");
    for (int i = 0; i < 2; i++) {
        archPrueba >> clientes[i];
    }
    clientes[2].dni = 0;
    for (int i = 0; i < 4; i++) {
        archPrueba >> productos[i];
    }
    strcpy(productos[4].codigo, "XXXXXXX");
    for (int i = 0; i < 10; i++) {
        archPrueba >> pedido;
        productos += pedido;
        clientes += pedido;
    }
    for (int i = 0; i < 2; i++) {
        archReporte << clientes[i];
    }
    for (int i = 0; i < 4; i++) {
        archReporte << endl;
        archReporte << productos[i];
    }
    return 0;
}
