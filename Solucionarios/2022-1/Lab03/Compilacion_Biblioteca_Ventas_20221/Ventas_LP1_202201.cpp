/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   2 de mayo de 2022, 12:10 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Estructuras.h"
#include "Ventas_LP1_202201.h"
using namespace std;

/* Sobrecargas de lectura */

ifstream& operator >>(ifstream& arch, Estructura_ClienteRegistrado& cliente) {
    int telefono, tamNombre;
    // Leer los datos del archivo
    arch >> cliente.dni;
    if (arch.eof()) return arch;
    arch >> cliente.nombre >> telefono;
    // Colocar descripción de la categoría
    tamNombre = strlen(cliente.nombre);
    if (cliente.nombre[tamNombre-2] == '-') {
        switch (cliente.nombre[tamNombre-1]) {
            case 'A':
                strcpy(cliente.categoria, "Cliente muy frecuente"); break;
            case 'B':
                strcpy(cliente.categoria, "Cliente frecuente"); break;
            case 'C':
                strcpy(cliente.categoria, "Cliente ocasional"); break;
        }
        cliente.nombre[tamNombre-2] = 0;
    } else {
        strcpy(cliente.categoria, "Cliente nuevo");
    }
    // Inicializar contadores
    cliente.numeroDePedidos = 0;
    cliente.montoTotalGastado = 0;
    return arch;
}

/* Sobrecargas de agregación */

void operator +=(Estructura_ClienteRegistrado arreglo[], Estructura_ClienteRegistrado& cliente) {
    int indice;
    // Buscar el índice a ingresar
    for (indice = 0; arreglo[indice].dni != 0; indice++);
    // Ingresar los datos del cliente
    arreglo[indice].dni = cliente.dni;
    strcpy(arreglo[indice].nombre, cliente.nombre);
    strcpy(arreglo[indice].categoria, cliente.categoria);
    arreglo[indice].montoTotalGastado = cliente.montoTotalGastado;
    arreglo[indice].numeroDePedidos = 0;
    for (int i = 0; i < cliente.numeroDePedidos; i++) {
        arreglo[indice] += cliente.pedidosRealizados[i];
    }
    // Preparar el siguiente cliente para poder buscar
    arreglo[indice+1].dni = 0;
}

void operator +=(Estructura_ClienteRegistrado& cliente, Estructura_PedidoRealizado& pedido) {
    strcpy(cliente.pedidosRealizados[cliente.numeroDePedidos].codigo, pedido.codigo);
    cliente.pedidosRealizados[cliente.numeroDePedidos].cantidad = pedido.cantidad;
    cliente.pedidosRealizados[cliente.numeroDePedidos].fecha = pedido.fecha;
    cliente.numeroDePedidos++;
}

void operator +=(Estructura_ProductosEnAlmacen arreglo[], Estructura_ProductosEnAlmacen& producto) {
    int cantidad, indice = -1;
    // Buscar el producto en el arreglo
    for (cantidad = 0; strcmp(arreglo[cantidad].codigo, "X") != 0; cantidad++) {
        if (strcmp(arreglo[cantidad].codigo, producto.codigo) == 0)
            indice = cantidad;
    }
    // Si el dato no se encontró, agregarlo al final del arreglo
    if (indice == -1) {
        strcpy(arreglo[cantidad].codigo, producto.codigo);
        strcpy(arreglo[cantidad].descripcion, producto.descripcion);
        arreglo[cantidad].descuento = producto.descuento;
        arreglo[cantidad].precioUnitario = producto.precioUnitario;
        strcpy(arreglo[cantidad+1].codigo, "X");
    }
}

/* Sobrecargas de impresión */

ofstream& operator <<(ofstream& arch, Estructura_ClienteRegistrado& cliente) {
    int dd, mm, aaaa;
    // Imprimir datos del cliente
    arch << fixed << setprecision(2);
    arch << right << setw(6) << "DNI" << setw(25) << "Nombre" << endl;
    arch << left << setw(10) << cliente.dni << cliente.nombre << endl;
    arch << cliente.categoria << endl;
    // Imprimir listado de pedidos
    arch << setw(5) << "No." << setw(10) << "Codigo" << setw(15) << "Cantidad"
            << "Fecha" << endl; 
    for (int i = 0; i < cliente.numeroDePedidos; i++) {
        dd = cliente.pedidosRealizados[i].fecha % 100;
        mm = (cliente.pedidosRealizados[i].fecha / 100) % 100;
        aaaa = cliente.pedidosRealizados[i].fecha / 10000;
        arch << right << setw(2) << i+1 << ")  "
                << left << setw(8) << cliente.pedidosRealizados[i].codigo
                << right << setw(8) << cliente.pedidosRealizados[i].cantidad
                << setw(6) << ' ' << setfill('0') << setw(2) << dd << '/'
                << setw(2) << mm << '/' << setw(4) << aaaa << setfill(' ') << endl;
    }
    // Imprimir monto total
    arch << "Monto total comprado: " << cliente.montoTotalGastado << endl;
    return arch;
}

ofstream& operator <<(ofstream& arch, Estructura_ProductosEnAlmacen arreglo[]) {
    // Imprimir cabecera
    arch << fixed << setprecision(2);
    arch << right << setw(50) << "PRODUCTOS ALMACENADOS" << endl;
    arch << left << setw(5) << "No." << setw(8) << "Codigo" << right
            << setw(25) << "Descripcion" << setw(30) << "Precio unitario"
            << setw(12) << "Descuento" << endl;
    // Imprimir listado de productos
    for (int i = 0; strcmp(arreglo[i].codigo, "X") != 0; i++) {
        arch << right << setw(2) << i+1 << ")  "
                << left << setw(8) << arreglo[i].codigo
                << setw(40) << arreglo[i].descripcion
                << right << setw(10) << arreglo[i].precioUnitario
                << setw(15) << arreglo[i].descuento << endl;
    }
    return arch;
}
