/*
 * File:   Cliente.h
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:36 AM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
#include "Pedido.h"
#include "ProductoEntregado.h"
using namespace std;

#define MAX_PROD_CLI 50

class Cliente {
public:
    Cliente();
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    // Encapsulamiento
    int GetDni() const;
    void SetDni(int dni);
    double GetMontoTotal() const;
    void SetMontoTotal(double monto_total);
    void GetNombre(char* nombre) const;
    void SetNombre(const char* nombre);
    int GetTelefono() const;
    void SetTelefono(int telefono);
    int GetCantidadProductosEntregados() const;
    // Sobrecargas
    void operator +=(Pedido &pedido);
    // Métodos adicionales
    void imprimirListaProductos(ofstream &arch);
private:
    int dni;
    char *nombre;
    int telefono;
    ProductoEntregado productos_entregados[MAX_PROD_CLI];
    int cantidad_productos_entregados;
    double monto_total;
};

// Lectura e impresión
bool operator >>(ifstream &arch, Cliente &cliente);
void operator <<(ofstream &arch, Cliente &cliente);

#endif /* CLIENTE_H */
