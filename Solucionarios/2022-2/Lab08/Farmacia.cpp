/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Farmacia.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Farmacia.h"
using namespace std;

Farmacia::Farmacia() {
}

Farmacia::Farmacia(const Farmacia& orig) {
}

Farmacia::~Farmacia() {
}

/* Métodos */

void Farmacia::cargaMedico() {
    ifstream arch("medicos.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo de medicos" << endl;
        exit(1);
    }
    int cont = 0;
    while (true) {
        lmedico[cont].leer(arch);
        if (arch.eof()) break;
        cont++;
    }
}

void Farmacia::leeRecetas() {
    ifstream arch("recetas.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo de recetas" << endl;
        exit(1);
    }
    int dd, mm, aaaa, fecha, dniPac, codMedico, codMedicina, cantMedicina,
            contSinRec = 0, contConRec = 0;
    char nomPac[50], c;
    // Leer línea por línea
    while (true) {
        arch >> dd;
        if (arch.eof()) break;
        arch >> c >> mm >> c >> aaaa >> c >> dniPac >> c;
        fecha = 10000*aaaa + 100*mm + dd;
        arch.getline(nomPac, 50, ',');
        arch >> codMedico >> c;
        while (true) {
            arch >> codMedicina >> c >> cantMedicina;
            // Verificar si es con o sin receta
            if ((codMedicina/10000) % 2 == 0) {
                lconreceta[contConRec].asignar(codMedicina, cantMedicina, fecha);
                lconreceta[contConRec].leer();
                lconreceta[contConRec].SetCodmed(codMedico);
                buscarMedico(lconreceta[contConRec]);
                contConRec++;
            } else {
                lsinreceta[contSinRec].asignar(codMedicina, cantMedicina, fecha);
                lsinreceta[contSinRec].leer();
                lsinreceta[contSinRec].SetDni(dniPac);
                lsinreceta[contSinRec].SetNombre(nomPac);
                contSinRec++;
            }
            if (arch.get() == '\n') break;
        }
    }
}

void Farmacia::buscarMedico(ConReceta& conreceta) {
    char especialidad[50];
    for (int i = 0; lmedico[i].GetCodigo(); i++) {
        if (lmedico[i].GetCodigo() == conreceta.GetCodmed()) {
            lmedico[i].GetEspecialidad(especialidad);
            conreceta.SetEspecialidad(especialidad);
            break;
        }
    }
}

void Farmacia::imprimirRecetas() {
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo del reporte" << endl;
        exit(1);
    }
    char buffer[50];
    // Imprimir medicamentos sin receta
    arch << left << setw(10) << "Codigo" << setw(40) << "Descripcion del Med."
            << setw(9) << "Cant." << setw(12) << "DNI" << "Nombre" << endl;
    imprimirLinea(arch, '=');
    for (int i = 0; lsinreceta[i].GetCodigo(); i++) {
        lsinreceta[i].imprimir(arch);
        lsinreceta[i].GetNombre(buffer);
        arch << setw(12) << lsinreceta[i].GetDni() << setw(4) << ' '
                << buffer << endl;
    }
    arch << endl;
    // Imprimir medicamentos con receta
    arch << left << setw(10) << "Codigo" << setw(40) << "Descripcion del Med."
            << setw(9) << "Cant." << setw(15) << "Cod. Medico" << "Especialidad" << endl;
    imprimirLinea(arch, '=');
    for (int i = 0; lconreceta[i].GetCodigo(); i++) {
        lconreceta[i].imprimir(arch);
        lconreceta[i].GetEspecialidad(buffer);
        arch << setw(12) << lconreceta[i].GetCodmed() << setw(7) << ' '
                << buffer << endl;
    }
}

void Farmacia::imprimirLinea(ofstream& arch, char c) {
    for (int i = 0; i < 100; i++) arch.put(c);
    arch << endl;
}
