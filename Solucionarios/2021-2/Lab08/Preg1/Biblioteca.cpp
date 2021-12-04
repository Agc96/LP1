/*
 * File:   Biblioteca.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 21 de noviembre de 2021, 05:43 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Biblioteca.h"
using namespace std;

Biblioteca::Biblioteca() {
}

Biblioteca::Biblioteca(const Biblioteca& orig) {
}

Biblioteca::~Biblioteca() {
}

void Biblioteca::generaCopias() {
    ifstream arch = abrirArchivo("Libros2.csv");
    int total = 0, cant;
    while (1) {
        llibros[total].leer(arch);
        cant = llibros[total].getCantidad();
        for (int i = 1; i < cant; i++) {
            llibros[total+i].copiar(llibros[total]);
            llibros[total+i].SetNumero(i+1);
        }
        total += cant;
        if (arch.eof()) break;
    }
}

void Biblioteca::actualizaLibros() {
    ifstream arch = abrirArchivo("RegistroDePrestamos2.csv");
    char codLibro[10], tipoUsu, c;
    int codUsu, numero, dd, mm, aaaa, hoy, fecha, posCopia;
    // Solicitar una fecha
    cout << "Ingrese una fecha en el formato AAAAMMDD: ";
    cin >> hoy;
    // Leer el archivo de préstamos
    while (1) {
        arch >> codUsu >> tipoUsu >> c;
        if (arch.eof()) break;
        arch.getline(codLibro, 10, ',');
        arch >> numero >> c >> dd >> c >> mm >> c >> aaaa;
        fecha = 10000*aaaa + 100*mm + dd;
        // Buscar la posición del libro
        posCopia = buscarCopia(codLibro, numero);
        if (posCopia != -1) {
            llibros[posCopia].actualizar(hoy, fecha);
        }
    }
}

int Biblioteca::buscarCopia(const char* codBuscado, int numBuscado) {
    char codLeido[10];
    int numLeido;
    for (int i = 0; llibros[i].getCantidad(); i++) {
        llibros[i].getCodigo(codLeido);
        numLeido = llibros[i].GetNumero();
        if (strcmp(codBuscado, codLeido) == 0 && numLeido == numBuscado) {
            return i;
        }
    }
    return -1;
}

void Biblioteca::imprimeCopias() {
    ofstream arch = crearArchivo("Reporte.txt");
    for (int i = 0; llibros[i].getCantidad(); i++) {
        llibros[i].imprimir(arch, i > 0);
    }
}

/* Métodos auxiliares */

ifstream Biblioteca::abrirArchivo(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream Biblioteca::crearArchivo(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}
