/*
 * Archivo: Tienda.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:21 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Tienda.h"
using namespace std;

Tienda::Tienda() {
}

Tienda::Tienda(const Tienda& orig) {
    cerr << "Constructor copia de Tienda" << endl;
}

Tienda::~Tienda() {
}

/* Métodos */

void Tienda::carga() {
    ifstream archCli, archPed;
    abrirArchivoEntrada(archPed, "pedidos3.csv");
    abrirArchivoEntrada(archCli, "clientes2.csv");
    int numCli = 0, numPed = 0;
    // Leer datos de los pedidos
    while (true) {
        lpedidos[numPed].leerPedido(archPed);
        if (archPed.eof()) break;
        buscarProducto(lpedidos[numPed]);
        numPed++;
    }
    // Leer datos de los clientes
    while (true) {
        lclientes[numCli].leer(archCli);
        if (archCli.eof()) break;
        numCli++;
    }
}

void Tienda::buscarProducto(Pedido& pedido) {
    ifstream archProd;
    abrirArchivoEntrada(archProd, "productos3.csv");
    while (true) {
        pedido.leerProducto(archProd);
        if (archProd.eof()) break;
        if (pedido.getCodigo() == pedido.getCodProd()) return;
    }
    pedido.setCodProd(0); // Para indicar que no se encontró
    pedido.setNombre("");
}

void Tienda::actualiza(int cantidad) {
    double total;
    char categoria;
    for (int i = 0; lpedidos[i].getCodigo(); i++) {
        total = lpedidos[i].getPrecio() * lpedidos[i].getCantidad();
        if (lpedidos[i].getCodigo() / 100000 == 4 && lpedidos[i].getStock() >= cantidad) {
            categoria = obtenerCategoria(lpedidos[i].getDni());
            switch (categoria) {
                case 'A':
                    total *= 0.5; // descuento del 50%
                    lpedidos[i].setObs("Descuento especial de 50%");
                    break;
                case 'B':
                    total *= 0.7; // descuento del 30%
                    lpedidos[i].setObs("Descuento especial de 30%");
                    break;
                case 'C':
                    total *= 0.9; // descuento del 10%
                    lpedidos[i].setObs("Descuento especial de 10%");
            }
        }
        lpedidos[i].setTotal(total);
    }
}

char Tienda::obtenerCategoria(int dni) {
    for (int i = 0; lclientes[i].GetDni(); i++) {
        if (dni == lclientes[i].GetDni()) return lclientes[i].GetCategoria();
    }
    return 0;
}

void Tienda::muestra() {
    ofstream archRep;
    abrirArchivoSalida(archRep, "Reporte.txt");
    // Imprimir la cabecera
    archRep << fixed << setprecision(2);
    archRep << left << setw(12) << "Fecha" << setw(8) << "Codigo"
            << setw(50) << "Descripcion del producto" << setw(7) << "Cant."
            << setw(10) << "Precio" << setw(7) << "Total"
            << "Observaciones" << endl;
    imprimirLinea(archRep, '=');
    // Imprimir el listado de pedidos
    for (int i = 0; lpedidos[i].getCodigo(); i++) {
        lpedidos[i].imprimirPedido(archRep);
    }
}

/* Métodos auxiliares */

void Tienda::abrirArchivoEntrada(ifstream& arch, const char *nombre) {
    arch.open(nombre, ios::in);
    if (!arch) {
        cerr << "No se pudo leer el archivo " << nombre << endl;
        exit(1);
    }
}

void Tienda::abrirArchivoSalida(ofstream& arch, const char *nombre) {
    arch.open(nombre, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nombre << endl;
        exit(1);
    }
}

void Tienda::imprimirLinea(ofstream& arch, char car) {
    for (int i = 0; i < 120; i++) arch.put(car);
    arch << endl;
}
