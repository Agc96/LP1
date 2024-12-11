/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Medicamento.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

#include <iostream>
#include <fstream>
using namespace std;

class Medicamento {
public:
    Medicamento();
    Medicamento(const Medicamento& orig);
    virtual ~Medicamento();
    // Métodos
    void asignar(int, int, int);
    void leer();
    void imprimir(ofstream &arch);
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    void GetNombre(char* nombre) const;
    void SetNombre(const char* nombre);
    int GetCantidad() const;
    void SetCantidad(int cantidad);
    double GetPrecio() const;
    void SetPrecio(double precio);
    int GetFecha() const;
    void SetFecha(int fecha);
private:
    int codigo;
    char *nombre;
    int cantidad;
    double precio;
    int fecha;
};

#endif /* MEDICAMENTO_H */

