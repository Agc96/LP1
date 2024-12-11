/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 08:21 PM
 */

#include <iostream>
#include <cstdlib>
#include "Estructuras.h"
#include "Funciones.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    struct Cliente clientes[150];
    struct Producto productos[200];
    leerClientes(clientes);
    leerProductos(productos);
    leerPedidos(clientes, productos);
    imprimirReporte(clientes, productos);
    return 0;
}
