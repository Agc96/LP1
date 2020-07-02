/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: FuncionesEx01_20201_Preg01.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de junio de 2020, 08:56 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "FuncionesEx01_20201_Preg01.h"
using namespace std;

#define MAX_CADENA 50

void leerDatos(char ***&cursos, int *&codProfesores, char **&profesores) {
    // TODO
}

void leerCursos(char ***&cursos) {
    // Abrir el archivo
    ifstream arch("Cursos.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo de cursos." << endl;
        exit(1);
    }
    // Iterar línea por línea
    char codCurso[MAX_CADENA], nomCurso[MAX_CADENA], especialidad[MAX_CADENA];
    while (true) {
        arch.getline(codCurso, MAX_CADENA, ',');
        if (arch.eof()) break;
        arch.getline(nomCurso, MAX_CADENA, ',');
        arch.getline(especialidad, MAX_CADENA);
    }
}

void leerProfesores(int *&codProfesores, char **&profesores) {
    // TODO
}

void imprimirDatos(char ***cursos, int *codProfesores, char **profesores) {
    // TODO
}
