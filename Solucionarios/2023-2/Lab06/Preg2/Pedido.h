/*
 * File:   Pedido.h
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_COD_PROD 10

class Pedido {
public:
    Pedido();
    Pedido(const Pedido& orig);
    virtual ~Pedido();
    // Encapsulamiento
    void GetCodigo(char* codigo) const;
    void SetCodigo(const char* codigo);
    int GetDniCliente() const;
    void SetDniCliente(int dni_cliente);
    double GetPrecioProducto() const;
    void SetPrecioProducto(double precio_producto);
private:
    char *codigo;
    int dni_cliente;
    double precio_producto;
};

// Lectura
bool operator >>(ifstream &arch, Pedido &pedido);

#endif /* PEDIDO_H */

