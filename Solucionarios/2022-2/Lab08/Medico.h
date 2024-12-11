/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Medico.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <fstream>
using namespace std;

class Medico {
public:
    Medico();
    Medico(const Medico& orig);
    virtual ~Medico();
    // Métodos
    void leer(ifstream &arch);
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    void GetEspecialidad(char* especialidad) const;
    void SetEspecialidad(const char* especialidad);
    void GetNombre(char* nombre) const;
    void SetNombre(const char* nombre);
private:
    int codigo;
    char *nombre;
    char *especialidad;
};

#endif /* MEDICO_H */

