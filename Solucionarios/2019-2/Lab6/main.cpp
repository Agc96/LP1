/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 11 de octubre de 2019, 10:06 AM
 */

#include "funciones.h"

int main(int argc, char** argv) {
    void* palets, *producto;
    leerPalets(palets);
    imprimirPalets(palets);
    leerProductos(producto);
    imprimirProductos(producto);
    ordenarProductos(producto);
    imprimirProductos(producto);
    cargaStock(palets, producto);
    return 0;
}
