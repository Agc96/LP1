/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   22 de septiembre de 2023, 12:45 PM
 */

#include "AsignacionDinamicaMemoriaPorIncrementos.h"

int main() {
    char ***productos, ***codigoPedidos;
    int *stock, *fechaPedidos, ***dniCantPedidos;
    double *precios;
    lecturaDeProductos("Productos.csv", productos, stock, precios);
    pruebaDeLecturaDeProductos("ReporteDeProductos.txt", productos, stock, precios);
    lecturaDePedidos("Pedidos.csv", fechaPedidos, codigoPedidos, dniCantPedidos);
    pruebaDeLecturaDePedidos("ReporteDePedidos.txt", fechaPedidos, codigoPedidos,
            dniCantPedidos);
    reporteDeEntregaDePedidos("ReporteDeEntregaDePedidos.txt", productos, stock,
            precios, fechaPedidos, codigoPedidos, dniCantPedidos);
    pruebaDeLecturaDeProductos("ReporteDeProductosFinal.txt", productos, stock,
            precios);
    return 0;
}
