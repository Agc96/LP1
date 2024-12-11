/*
 * File:   Almacen.h
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#ifndef ALMACEN_H
#define ALMACEN_H

#include "Cliente.h"
#include "Producto.h"
#define MAX_CLIENTES 150
#define MAX_PRODUCTOS 200

class Almacen {
public:
    Almacen();
    Almacen(const Almacen& orig);
    virtual ~Almacen();
    // Métodos
    void cargar_clientes();
    void cargar_productos();
    void cargar_pedidos();
    void mostrar_datos();
private:
    Cliente arreglo_clientes[MAX_CLIENTES];
    int cantidad_clientes;
    Producto arreglo_productos[MAX_PRODUCTOS];
    int cantidad_productos;
    // Métodos auxiliares
    int buscarCliente(int dni);
    int buscarProducto(char *codigo);
    void imprimirLinea(ofstream &arch, char car, int cant);
};

#endif /* ALMACEN_H */

