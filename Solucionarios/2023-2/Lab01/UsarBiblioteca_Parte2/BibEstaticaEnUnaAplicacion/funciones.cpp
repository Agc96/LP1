/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 08:27 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "AperturaDeArchivos.h"
#include "Estructuras.h"
#include "Sobrecargas.h"
#include "Funciones.h"
using namespace std;

void leerClientes(struct Cliente *clientes) {
    ifstream arch;
    AperturaDeUnArchivoDeTextosParaLeer(arch, "Clientes.csv");
    int cantClientes = 0;
    bool resultado;
    while (true) {
        resultado = arch >> clientes[cantClientes];
        if (!resultado) break;
        cantClientes++;
    }
    clientes[cantClientes].dni = 0;
}

void leerProductos(struct Producto *productos) {
    ifstream arch;
    AperturaDeUnArchivoDeTextosParaLeer(arch, "Productos.csv");
    int cantProductos = 0;
    bool resultado;
    while (true) {
        resultado = arch >> productos[cantProductos];
        if (not resultado) break;
        cantProductos++;
    }
    strcpy(productos[cantProductos].codigo, "XXXXXXX");
}

void leerPedidos(struct Cliente *clientes, struct Producto *productos) {
    ifstream arch;
    AperturaDeUnArchivoDeTextosParaLeer(arch, "Pedidos.csv");
    struct Pedido pedido;
    while (true) {
        arch >> pedido;
        if (arch.eof()) break;
        productos += pedido;
        clientes += pedido;
    }
}

void imprimirReporte(struct Cliente *clientes, struct Producto *productos) {
    ofstream arch;
    AperturaDeUnArchivoDeTextosParaEscribir(arch, "Reporte.txt");
    arch << "LISTADO DE CLIENTES" << endl;
    imprimirLinea(arch, '=');
    for (int i = 0; clientes[i].dni != 0; i++) {
        arch << clientes[i];
    }
    arch << endl;
    arch << "LISTADO DE PRODUCTOS" << endl;
    imprimirLinea(arch, '=');
    for (int i = 0; strcmp(productos[i].codigo, "XXXXXXX") != 0; i++) {
        arch << productos[i];
        imprimirLinea(arch, '-');
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < 120; i++) {
        arch.put(car);
    }
    arch << endl;
}
