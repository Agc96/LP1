/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Sobrecargas.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 06:40 PM
 */

#ifndef SOBRECARGAS_H
#define SOBRECARGAS_H

#include <iostream>
#include <fstream>
#include "Estructuras.h"
using namespace std;

bool operator >>(ifstream &, Cliente &);
bool operator >>(ifstream &, Producto &);
bool operator >>(ifstream &, Pedido &);

void operator +=(Cliente *, Pedido &);
bool operator +=(Producto *, Pedido &);

void operator <<(ofstream &, Cliente &);
void operator <<(ofstream &, Producto &);

#endif /* SOBRECARGAS_H */

