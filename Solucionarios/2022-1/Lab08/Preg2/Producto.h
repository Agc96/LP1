/*
 * Archivo: Producto.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
using namespace std;

class Producto {
public:
    Producto();
    Producto(const Producto& orig);
    virtual ~Producto();
    // Métodos
    void leerProducto(ifstream&);
    // Encapsulamiento
    int getCodProd() const;
    void setCodProd(int codprod);
    void getNombre(char* nombre) const;
    void setNombre(const char* nombre);
    double getPrecio() const;
    void setPrecio(double precio);
    int getStock() const;
    void setStock(int stock);
private:
    int codprod;
    char *nombre;
    double precio;
    int stock;
};

#endif /* PRODUCTO_H */

