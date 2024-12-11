/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de mayo de 2022, 09:24 AM
 */

#include "Estructuras.h"
#include "Funciones.h"

int main() {
    Estructura_ClienteRegistrado arrClientes[20];
    Estructura_ProductosEnAlmacen arrProductos[150];
    procesarClientes(arrClientes);
    procesarProductos(arrClientes, arrProductos);
    generarReporte(arrClientes, arrProductos);
    return 0;
}
