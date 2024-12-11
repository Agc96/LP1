/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Farmacia.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#ifndef FARMACIA_H
#define FARMACIA_H

#include <iostream>
#include <fstream>
#include "Medico.h"
#include "ConReceta.h"
#include "SinReceta.h"
using namespace std;

class Farmacia {
public:
    Farmacia();
    Farmacia(const Farmacia& orig);
    virtual ~Farmacia();
    // Métodos
    void cargaMedico();
    void leeRecetas();
    void imprimirRecetas();
private:
    Medico lmedico[50];
    SinReceta lsinreceta[1000];
    ConReceta lconreceta[1000];
    // Métodos auxiliares
    void buscarMedico(ConReceta& conreceta);
    void imprimirLinea(ofstream& arch, char c);
};

#endif /* FARMACIA_H */
