/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:30 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Tesoreria.h"
using namespace std;

#define MAX_LINEA 100

Tesoreria::Tesoreria() {
    // No es necesario hacer nada aquí
}

Tesoreria::Tesoreria(const Tesoreria& orig) {
}

Tesoreria::~Tesoreria() {
    // No es necesario hacer nada aquí
}

void Tesoreria::cargaalumnos() {
    ifstream arch;
    char tipo;
    abrirArchivoEntrada(arch, "Alumnos.csv");
    // Insertar ordenadamente en el árbol
    while (true) {
        arch >> tipo;
        if (arch.eof()) break;
        aboleta.insertarAlumno(arch, tipo);
    }
}

void Tesoreria::actualizaboleta() {
    ifstream arch;
    int escala;
    abrirArchivoEntrada(arch, "Escalas.csv");
    // Leer escalas
    while (true) {
        arch >> escala;
        if (arch.eof()) break;
        aboleta.insertarEscala(arch, escala);
    }
    // Actualizar totales
    aboleta.actualizarTotales();
}

void Tesoreria::imprimeboleta() {
    ofstream arch;
    abrirArchivoSalida(arch, "Reporte.txt");
    arch << fixed << setprecision(2);
    // Imprimir cabecera
    arch << left << setw(12) << "Codigo" << setw(MAX_NOM_ALUMNO) << "Nombre"
            << setw(8) << "Escala" << setw(7) << "Cred."
            << setw(12) << "Licencia" << "Total" << endl;
    imprimirLinea(arch, '=');
    // Impriir árbol de boletas
    aboleta.imprimir(arch);
}

/* Métodos auxiliares */

void Tesoreria::abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void Tesoreria::abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void Tesoreria::imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++) arch.put(car);
    arch << endl;
}
