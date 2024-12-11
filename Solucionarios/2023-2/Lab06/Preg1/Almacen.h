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
private:
    Cliente arreglo_clientes[MAX_CLIENTES];
    int cantidad_clientes;
    Producto arreglo_productos[MAX_PRODUCTOS];
    int cantidad_productos;
};

#endif /* ALMACEN_H */

