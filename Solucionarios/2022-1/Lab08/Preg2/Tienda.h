/*
 * Archivo: Tienda.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:21 PM
 */

#ifndef TIENDA_H
#define TIENDA_H

#include <iostream>
#include <fstream>
#include "Cliente.h"
#include "Pedido.h"
using namespace std;

class Tienda {
public:
    Tienda();
    Tienda(const Tienda& orig);
    virtual ~Tienda();
    // Métodos
    void carga();
    void actualiza(int);
    void muestra();
private:
    Pedido lpedidos[150];
    Cliente lclientes[20];
    // Métodos auxiliares
    void buscarProducto(Pedido&);
    char obtenerCategoria(int);
    void abrirArchivoEntrada(ifstream&, const char *);
    void abrirArchivoSalida(ofstream&, const char *);
    void imprimirLinea(ofstream&, char);
};

#endif /* TIENDA_H */
