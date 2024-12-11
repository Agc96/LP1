/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   2 de mayo de 2022, 08:52 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "AperturaDeArchivos.h"
#include "Estructuras.h"
#include "Funciones.h"
#include "Ventas_LP1_202201.h"
using namespace std;

void procesarClientes(Estructura_ClienteRegistrado arrClientes[]) {
    ifstream arch;
    Estructura_ClienteRegistrado cliente;
    // Inicialización de variables
    AperturaDeUnArchivoDeTextosParaLeer(arch, "Clientes.txt");
    arrClientes[0].dni = 0;
    // Leer cliente por cliente
    while (true) {
        arch >> cliente;
        if (arch.eof()) break;
        arrClientes += cliente;
    }
}

void procesarProductos(Estructura_ClienteRegistrado arrClientes[],
        Estructura_ProductosEnAlmacen productos[]) {
    ifstream arch;
    Estructura_ProductosEnAlmacen producto;
    Estructura_PedidoRealizado pedido;
    int dni, indice;
    // Inicialización de variables
    AperturaDeUnArchivoDeTextosParaLeer(arch, "Pedidos.txt");
    strcpy(productos[0].codigo, "X");
    // Leer producto por producto
    while (true) {
        leerDatosProducto(arch, producto, pedido, dni);
        if (arch.eof()) break;
        // Agregar producto al arreglo
        productos += producto;
        // Buscar cliente y actualizar la cantidad de productos y el monto
        indice = buscarCliente(arrClientes, dni);
        if (indice != -1) {
            arrClientes[indice] += pedido;
            arrClientes[indice].montoTotalGastado += producto.precioUnitario *
                    pedido.cantidad * (1 - producto.descuento/100);
        }
    }
}

void leerDatosProducto(ifstream& arch, Estructura_ProductosEnAlmacen& producto,
        Estructura_PedidoRealizado& pedido, int& dni) {
    int dd, mm, aaaa;
    char c;
    // Leer datos del producto
    arch >> producto.codigo;
    if (arch.eof()) return;
    strcpy(pedido.codigo, producto.codigo);
    arch >> producto.descripcion >> pedido.cantidad;
    if (arch.fail()) {
        arch.clear();
        arch >> c >> producto.descuento >> pedido.cantidad;
    } else {
        producto.descuento = 0;
    }
    arch >> producto.precioUnitario >> dni >> dd >> c >> mm >> c >> aaaa;
    pedido.fecha = 10000*aaaa + 100*mm + dd;
}

int buscarCliente(Estructura_ClienteRegistrado arrClientes[], int dni) {
    for (int i = 0; arrClientes[i].dni != 0; i++) {
        if (arrClientes[i].dni == dni) return i;
    }
    return -1; // No encontrado
}

void generarReporte(Estructura_ClienteRegistrado clientes[], Estructura_ProductosEnAlmacen productos[]) {
    ofstream arch;
    AperturaDeUnArchivoDeTextosParaEscribir(arch, "Reporte.txt");
    // Impresión de productos
    arch << fixed << setprecision(2);
    arch << right << setw(54) << "EMPRESA COMERCIALIZADORA ABC" << endl;
    arch << productos << endl;
    // Impresión de clientes
    arch << right << setw(50) << "PEDIDOS POR CLIENTE" << endl;
    for (int i = 0; clientes[i].dni != 0; i++) {
        arch << clientes[i] << endl;
    }
}
