/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   2 de mayo de 2022, 08:52 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Estructuras.h"
using namespace std;

void leerProducto(ifstream& arch, Estructura_ProductosEnAlmacen& producto,
        Estructura_PedidoRealizado& pedido) {
    int dni, dd, mm, aaaa;
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
