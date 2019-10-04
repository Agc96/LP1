/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 4 de octubre de 2019, 11:07 AM
 */

#include "funciones.h"
using namespace std;

int main(int argc, char** argv) {
    char ***almacenes, **codigoProd, **nombreProd;
    leerPalets(almacenes);
    imprimirPalets(almacenes);
    leerProductos(codigoProd, nombreProd);
    imprimirProductos(codigoProd, nombreProd);
    ordenarProductos(codigoProd, nombreProd);
    imprimirProductos(codigoProd, nombreProd);
    cuentaProductos(almacenes, codigoProd, nombreProd);
    return 0;
}
