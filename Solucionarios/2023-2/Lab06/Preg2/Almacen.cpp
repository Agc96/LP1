/*
 * File:   Almacen.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Almacen.h"
#include "Pedido.h"
using namespace std;

#define MAX_LIN_CLI 200
#define MAX_LIN_PROD 120
#define NO_ENCONTRADO -1

Almacen::Almacen() {
    cantidad_clientes = 0;
    cantidad_productos = 0;
}

Almacen::Almacen(const Almacen& orig) {
}

Almacen::~Almacen() {
}

/* Métodos */

void Almacen::cargar_clientes() {
    ifstream arch("Clientes.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Clientes.csv" << endl;
        exit(1);
    }
    while (arch >> arreglo_clientes[cantidad_clientes]) cantidad_clientes++;
}

void Almacen::cargar_productos() {
    ifstream arch("Productos.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Productos.csv" << endl;
        exit(1);
    }
    while (arch >> arreglo_productos[cantidad_productos]) cantidad_productos++;
}

void Almacen::cargar_pedidos() {
    ifstream arch("Pedidos.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Pedidos.csv" << endl;
        exit(1);
    }
    Pedido pedido;
    int posCli, posProd;
    char codigo[MAX_COD_PROD];
    while (arch >> pedido) {
        // Actualizar producto
        pedido.GetCodigo(codigo);
        posProd = buscarProducto(codigo);
        if (posProd == NO_ENCONTRADO) continue;
        if (arreglo_productos[posProd] += pedido) {
            // Actualizar cliente
            posCli = buscarCliente(pedido.GetDniCliente());
            if (posCli == NO_ENCONTRADO) continue;
            arreglo_clientes[posCli] += pedido;
        }
    }
}

void Almacen::mostrar_datos() {
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    arch << fixed << setprecision(2);
    arch << "REPORTE DE CLIENTES" << endl;
    imprimirLinea(arch, '=', MAX_LIN_CLI);
    for (int i = 0; i < cantidad_clientes; i++) {
        arch << arreglo_clientes[i];
    }
    arch << endl << "REPORTE DE PRODUCTOS" << endl;
    imprimirLinea(arch, '=', MAX_LIN_PROD);
    for (int i = 0; i < cantidad_productos; i++) {
        arch << arreglo_productos[i];
        imprimirLinea(arch, '-', MAX_LIN_PROD);
    }
}

int Almacen::buscarProducto(char *codBuscado) {
    char codigo[MAX_COD_PROD];
    for (int i = 0; i < cantidad_productos; i++) {
        arreglo_productos[i].GetCodigo(codigo);
        if (strcmp(codigo, codBuscado) == 0)
            return i;
    }
    return NO_ENCONTRADO;
}

int Almacen::buscarCliente(int dni) {
    for (int i = 0; i < cantidad_clientes; i++) {
        if (arreglo_clientes[i].GetDni() == dni)
            return i;
    }
    return NO_ENCONTRADO;
}

void Almacen::imprimirLinea(ofstream &arch, char car, int cant) {
    for (int i = 0; i < cant; i++)
        arch.put(car);
    arch << endl;
}
