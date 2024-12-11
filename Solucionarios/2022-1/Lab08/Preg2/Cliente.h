/*
 * Archivo: Cliente.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
using namespace std;

class Cliente {
public:
    Cliente();
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    // Métodos
    void leer(ifstream&);
    void imprimir(ofstream&);
    // Encapsulamiento
    char GetCategoria() const;
    void SetCategoria(char categoria);
    int GetDni() const;
    void SetDni(int dni);
    void GetNombre(char* nombre) const;
    void SetNombre(const char* nombre);
private:
    int dni;
    char *nombre;
    char categoria;
};

#endif /* CLIENTE_H */
