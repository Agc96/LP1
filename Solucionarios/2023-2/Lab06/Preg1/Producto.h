/*
 * File:   Producto.h
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include "Pedido.h"
using namespace std;

#define MAX_CLI_PROD 100

class Producto {
public:
    Producto();
    Producto(const Producto& orig);
    virtual ~Producto();
    // Encapsulamiento
    void GetCodigo(char* codigo) const;
    void SetCodigo(const char* codigo);
    void GetDescripcion(char* descripcion) const;
    void SetDescripcion(const char* descripcion);
    double GetPrecio() const;
    void SetPrecio(double precio);
    int GetStock() const;
    void SetStock(int stock);
    int GetCantidadClientesNoServidos() const;
    int GetCantidadClientesServidos() const;
    // Agregación
    bool operator +=(Pedido &);
    // Métodos adicionales
    void imprimirListaClientes(ofstream &);
private:
    char *codigo;
    char *descripcion;
    double precio;
    int stock;
    int clientes_servidos[MAX_CLI_PROD];
    int cantidad_clientes_servidos;
    int clientes_no_servidos[MAX_CLI_PROD];
    int cantidad_clientes_no_servidos;
};

// Lectura e impresión
bool operator >>(ifstream &arch, Producto &producto);
void operator <<(ofstream &arch, Producto &producto);

#endif /* PRODUCTO_H */
