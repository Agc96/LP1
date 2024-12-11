/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 06:36 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "AperturaDeArchivos.h"
#include "Estructuras.h"
#include "Sobrecargas.h"

int main() {
    ifstream archPrueba;
    ofstream archReporte;
    struct Cliente clientes[10];
    struct Producto productos[10];
    struct Pedido pedido;
    bool resultado;
    AperturaDeUnArchivoDeTextosParaLeer(archPrueba, "Prueba.txt");
    AperturaDeUnArchivoDeTextosParaEscribir(archReporte, "Reporte.txt");
    archReporte << fixed << setprecision(2);
    archReporte << "arch >> cliente:";
    for (int i = 0; i < 2; i++) {
        resultado = archPrueba >> clientes[i];
        archReporte << setw(2) << resultado; 
    }
    clientes[2].dni = 0;
    archReporte << endl << "arch >> producto:";
    for (int i = 0; i < 4; i++) {
        resultado = archPrueba >> productos[i];
        archReporte << setw(2) << resultado; 
    }
    strcpy(productos[4].codigo, "XXXXXXX");
    archReporte << endl << "arch >> pedido:";
    for (int i = 0; i < 9; i++) {
        resultado = archPrueba >> pedido;
        archReporte << setw(2) << resultado;
        resultado = productos += pedido;
        clientes += pedido;
        archReporte << setw(2) << resultado;
    }
    archReporte << endl;
    for (int i = 0; i < 2; i++) {
        archReporte << clientes[i];
    }
    for (int i = 0; i < 4; i++) {
        archReporte << endl;
        archReporte << productos[i];
    }
    return 0;
}
