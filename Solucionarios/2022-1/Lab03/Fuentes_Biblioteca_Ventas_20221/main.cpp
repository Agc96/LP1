/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Created on 2 de mayo de 2022, 12:00 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "AperturaDeArchivos.h"
#include "Estructuras.h"
#include "Ventas_LP1_202201.h"
#include "Funciones.h"
using namespace std;

int main() {
    ifstream archPruebas;
    ofstream archReporte;
    Estructura_ClienteRegistrado arrClientes[6], cliente;
    Estructura_ProductosEnAlmacen arrProductos[6], producto;
    Estructura_PedidoRealizado pedido;
    // Inicialización
    AperturaDeUnArchivoDeTextosParaLeer(archPruebas, "Pruebas.txt");
    AperturaDeUnArchivoDeTextosParaEscribir(archReporte, "Reporte.txt");
    arrClientes[0].dni = 0;
    strcpy(arrProductos[0].codigo, "X");
    // Pruebas de lectura y asignación
    for (int i = 0; i < 5; i++) {
        archPruebas >> cliente;
        arrClientes += cliente;
    }
    for (int i = 0; i < 5; i++) {
        leerProducto(archPruebas, producto, pedido);
        arrClientes[i] += pedido;
        arrProductos += producto;
        arrClientes[i].montoTotalGastado += pedido.cantidad *
                producto.precioUnitario * (1 - producto.descuento/100);
    }
    // Prueba de impresión
    archReporte << arrProductos << endl;
    for (int i = 0; i < 5; i++) {
        archReporte << arrClientes[i] << endl;
    }
    return 0;
}
