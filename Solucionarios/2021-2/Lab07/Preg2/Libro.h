/*
 * File:   Libro.h
 * Author: Anthony Gutiérrez
 *
 * Created on 12 de noviembre de 2021, 09:18 AM
 */

#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
#include <fstream>
#include "LibroPrestado.h"
using namespace std;

class Libro {
public:
    Libro();
    Libro(const Libro& orig);
    virtual ~Libro();
    // Métodos
    ifstream& leer(ifstream& arch);
    ofstream& imprimir(ofstream& arch);
    // Sobrecargas
    void operator +=(LibroPrestado& prestamo);
    // Encapsulamiento
    void GetAutor(char* autor) const;
    void SetAutor(char* autor);
    int GetCantAdm() const;
    void SetCantAdm(int cantAdm);
    int GetCantDoc() const;
    void SetCantDoc(int cantDoc);
    int GetCantEst() const;
    void SetCantEst(int cantEst);
    void GetCodigo(char* codigo) const;
    void SetCodigo(char* codigo);
    double GetPrecio() const;
    void SetPrecio(double precio);
    int GetPrestados() const;
    void SetPrestados(int prestados);
    int GetStock() const;
    void SetStock(int stock);
    void GetTitulo(char* titulo) const;
    void SetTitulo(char* titulo);
private:
    char *codigo;
    char *titulo;
    char *autor;
    int stock;
    double precio;
    int prestados;
    int cantEst;
    int cantDoc;
    int cantAdm;
    // Métodos auxiliares
    void imprimirLinea(ofstream& arch, char c);
};

ifstream& operator >>(ifstream& arch, Libro& libro);
ofstream& operator <<(ofstream& arch, Libro& libro);

#endif /* LIBRO_H */

