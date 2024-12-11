/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:43 PM
 */

#include "Farmacia.h"

int main() {
    Farmacia ofarma;
    ofarma.cargaMedico();
    ofarma.leeRecetas();
    ofarma.imprimirRecetas();
    return 0;
}
