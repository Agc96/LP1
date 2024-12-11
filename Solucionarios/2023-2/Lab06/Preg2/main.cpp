/*
 * File:   main.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:32 AM
 */

#include "Almacen.h"

int main(int argc, char** argv) {
    Almacen almacen;
    almacen.cargar_clientes();
    almacen.cargar_productos();
    almacen.cargar_pedidos();
    almacen.mostrar_datos();
    return 0;
}
