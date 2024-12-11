/*
 * Archivo: Pedido.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include <iostream>
#include <fstream>
#include "Producto.h"
using namespace std;

class Pedido : public Producto {
public:
    Pedido();
    Pedido(const Pedido& orig);
    virtual ~Pedido();
    // Métodos
    void leerPedido(ifstream&);
    void imprimirPedido(ofstream&);
    // Encapsulamiento
    int getCantidad() const;
    void setCantidad(int cantidad);
    int getCodigo() const;
    void setCodigo(int codigo);
    int getDni() const;
    void setDni(int dni);
    int getFecha() const;
    void setFecha(int fecha);
    void getObs(char* obs) const;
    void setObs(const char* obs);
    double getTotal() const;
    void setTotal(double total);
private:
    int codigo;
    int cantidad;
    int dni;
    int fecha;
    double total;
    char *obs;
    // Métodos auxiliares
    void imprimirFecha(ofstream&);
};

#endif /* PEDIDO_H */
