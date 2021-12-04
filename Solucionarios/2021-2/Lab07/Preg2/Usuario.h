/*
 * File:   Usuario.h
 * Author: Anthony Gutiérrez
 *
 * Created on 12 de noviembre de 2021, 09:16 AM
 */

#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <fstream>
#include "LibroPrestado.h"
using namespace std;

#define MAX_LIBROS_PRESTADOS 20

class Usuario {
public:
    Usuario();
    Usuario(const Usuario& orig);
    virtual ~Usuario();
    // Métodos
    ifstream& leer(ifstream& arch);
    ofstream& imprimir(ofstream& arch);
    // Sobrecargas
    void operator +=(LibroPrestado& prestamo);
    void operator *(int fecha);
    // Encapsulamiento
    int GetCarne() const;
    void SetCarne(int carne);
    void GetNombre(char *nombre) const;
    void SetNombre(char *nombre);
    char GetTipo() const;
    void SetTipo(char tipo);
    int GetCondicion() const;
    void SetCondicion(int condicion);
private:
    int carne;
    char tipo;
    char *nombre;
    LibroPrestado libPrest[MAX_LIBROS_PRESTADOS];
    int numLibPrest;
    int condicion;
    // Métodos auxiliares
    void imprimirTipo(ofstream& arch);
    void imprimirCondicion(ofstream& arch);
};

ifstream& operator >>(ifstream& arch, Usuario& usuario);
ofstream& operator <<(ofstream& arch, Usuario& usuario);

#endif /* USUARIO_H */
