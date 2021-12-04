/*
 * File:   Libro.h
 * Author: Anthony Gutiérrez
 *
 * Created on 21 de noviembre de 2021, 05:40 PM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
#include <fstream>
using namespace std;

class Libro {
public:
    Libro();
    Libro(const Libro& orig);
    virtual ~Libro();
    // Métodos
    void leer(ifstream& arch);
    void copiar(const Libro& orig);
    void imprimir(ofstream& arch, bool lineaInicial);
    // Encapsulamiento
    void getAutor(char* autor) const;
    void setAutor(char* autor);
    int getCantidad() const;
    void setCantidad(int cantidad);
    void getCodigo(char* codigo) const;
    void setCodigo(char* codigo);
    double getPrecio() const;
    void setPrecio(double precio);
    void getTitulo(char* titulo) const;
    void setTitulo(char* titulo);
private:
    char* codigo;
    char* titulo;
    char* autor;
    int cantidad;
    double precio;
    // Métodos auxiliares
    void imprimirLinea(ofstream&, char);
};

#endif /* LIBRO_H */
