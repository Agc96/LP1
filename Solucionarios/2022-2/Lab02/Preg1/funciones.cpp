/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de septiembre de 2022, 06:15 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

void separarMedicosConsultas() {
    fstream archEntrada = abrirArchivo("Medico-Paciente-Medicinas.txt", ios::in);
    fstream archReporte = abrirArchivo("Reporte.txt", ios::out);
    inicializarArchBin();
    leerMedicosConsultas(archEntrada);
    archReporte << fixed << setprecision(2);
    reporteMedicos(archReporte);
    reportePacientes(archReporte);
    reporteMedicinas(archReporte);
    reporteConsultas(archReporte);
}

void inicializarArchBin() {
    abrirArchivo("Pacientes.bin", ios::out | ios::binary);
    abrirArchivo("Medicinas.bin", ios::out | ios::binary);
}

void leerMedicosConsultas(fstream& archEntrada) {
    fstream archMedicos = abrirArchivo("Medicos.txt", ios::out);
    fstream archPacientes = abrirArchivo("Pacientes.bin", ios::in | ios::out | ios::binary);
    fstream archMedicinas = abrirArchivo("Medicinas.bin", ios::in | ios::out | ios::binary);
    fstream archConsultas = abrirArchivo("Consultas.txt", ios::out);
    char codMed[8], nomMed[60], nomPac[20], codAten[8], c, descMed2[40];
    int dniPac, dd, mm, aaaa, fecha, cantMed2, codMed2;
    double precMed2, gasto = 0;
    while (true) {
        archEntrada >> dniPac;
        if (archEntrada.eof()) break;
        if (archEntrada.fail()) {
            archEntrada.clear();
            archEntrada >> codMed >> nomMed;
            agregarMedico(archMedicos, codMed, nomMed);
        } else {
            archEntrada >> nomPac >> codAten >> dd >> c >> mm >> c >> aaaa >> cantMed2;
            fecha = 10000*aaaa + 100*mm + dd;
            agregarPaciente(archPacientes, dniPac, nomPac, gasto);
            archConsultas << dniPac << ' ' << codAten << ' ' << fecha << ' ' << cantMed2;
            for (int i = 0; i < cantMed2; i++) {
                archEntrada >> codMed2 >> descMed2 >> precMed2;
                agregarMedicina(archMedicinas, codMed2, descMed2, precMed2);
                archConsultas << ' ' << codMed2;
            }
            archConsultas << endl;
        }
    }
}

void agregarMedico(fstream &archMedicos, char *codMed, char *nomMed) {
    char *especMed;
    for (int i = strlen(nomMed)-1; i >= 0; i--) {
        if (nomMed[i] == '_') {
            especMed = &(nomMed[i+1]);
            nomMed[i] = 0;
            break;
        }
    }
    archMedicos << codMed << ' ' << nomMed << ' ' << especMed << endl;
}

void agregarPaciente(fstream &archPacientes, int dniPac, char *nomPac, double gasto) {
    int tamReg, numReg, dniLeido;
    tamReg = sizeof(int) + sizeof(char)*20 + sizeof(double);
    numReg = obtenerNumReg(archPacientes, tamReg);
    for (int i = 0; i < numReg; i++) {
        archPacientes.seekg(i*tamReg, ios::beg);
        archPacientes.read(reinterpret_cast<char*>(&dniLeido), sizeof(int));
        // Si los DNIs coinciden, ya no es necesario insertar los datos
        if (dniPac == dniLeido) return;
    }
    // Si el DNI no se ha encontrado, insertar al final del archivo
    archPacientes.seekg(0, ios::end);
    archPacientes.write(reinterpret_cast<const char*>(&dniPac), sizeof(int));
    archPacientes.write(reinterpret_cast<const char*>(nomPac), sizeof(char)*20);
    archPacientes.write(reinterpret_cast<const char*>(&gasto), sizeof(double));
}

void agregarMedicina(fstream &archMedicinas, int codMed2, char *descMed2, double precMed2) {
    int tamReg, numReg, codMedLeido;
    tamReg = sizeof(int) + sizeof(char)*40 + sizeof(double);
    numReg = obtenerNumReg(archMedicinas, tamReg);
    for (int i = 0; i < numReg; i++) {
        archMedicinas.seekg(i*tamReg, ios::beg);
        archMedicinas.read(reinterpret_cast<char*>(&codMedLeido), sizeof(int));
        // Si los códigos coinciden, ya no es necesario insertar los datos
        if (codMed2 == codMedLeido) return;
    }
    // Si el código no se ha encontrado, insertar al final del archivo
    archMedicinas.seekg(0, ios::end);
    archMedicinas.write(reinterpret_cast<const char*>(&codMed2), sizeof(int));
    archMedicinas.write(reinterpret_cast<const char*>(descMed2), sizeof(char)*40);
    archMedicinas.write(reinterpret_cast<const char*>(&precMed2), sizeof(double));
}

void reporteMedicos(fstream &archRep) {
    fstream archMed = abrirArchivo("Medicos.txt", ios::in);
    char codMed[8], nomMed[40], especMed[20];
    // Imprimir cabecera
    archRep << setw(50) << "LISTADO DE MÉDICOS" << endl;
    imprimirLinea(archRep, '=');
    archRep << left << setw(10) << "Codigo" << setw(40) << "Nombre"
            << "Especialidad" << endl;
    imprimirLinea(archRep, '-');
    // Imprimir listado de médicos
    while (true) {
        archMed >> codMed >> nomMed >> especMed;
        if (archMed.eof()) break;
        archRep << setw(10) << codMed << setw(40) << nomMed << especMed << endl;
    }
    archRep << endl;
}

void reportePacientes(fstream &archRep) {
    fstream archPac = abrirArchivo("Pacientes.bin", ios::in | ios::binary);
    int dniPac;
    char nomPac[20];
    double gasto;
    // Imprimir cabecera
    archRep << right << setw(50) << "LISTADO DE PACIENTES" << endl;
    imprimirLinea(archRep, '=');
    archRep << left << setw(10) << "DNI" << setw(20) << "Nombre"
            << "Gasto" << endl;
    imprimirLinea(archRep, '-');
    // Imprimir listado de pacientes
    while (true) {
        archPac.read(reinterpret_cast<char*>(&dniPac), sizeof(int));
        if (archPac.eof()) break;
        archPac.read(reinterpret_cast<char*>(nomPac), sizeof(char)*20);
        archPac.read(reinterpret_cast<char*>(&gasto), sizeof(double));
        archRep << setfill('0') << setw(8) << dniPac << "  " << setfill(' ')
                << left << setw(20) << nomPac << right << setw(5) << gasto << endl;
    }
    archRep << endl;
}

void reporteMedicinas(fstream &archRep) {
    fstream archMed = abrirArchivo("Medicinas.bin", ios::in | ios::binary);
    int codMed2;
    char descMed2[40];
    double precMed2;
    // Imprimir cabecera
    archRep << right << setw(50) << "LISTADO DE MEDICINAS" << endl;
    imprimirLinea(archRep, '=');
    archRep << left << setw(8) << "Codigo" << setw(40) << "Descripcion"
            << "Precio" << endl;
    imprimirLinea(archRep, '-');
    // Imprimir listado de medicinas
    while (true) {
        archMed.read(reinterpret_cast<char*>(&codMed2), sizeof(int));
        if (archMed.eof()) break;
        archMed.read(reinterpret_cast<char*>(descMed2), sizeof(char)*40);
        archMed.read(reinterpret_cast<char*>(&precMed2), sizeof(double));
        archRep << left << setw(8) << codMed2 << setw(40) << descMed2
                << right << setw(6) << precMed2 << endl;
    }
    archRep << endl;
}

void reporteConsultas(fstream &archRep) {
    fstream archCon = abrirArchivo("Consultas.txt", ios::in);
    char codAten[8];
    int dniPac, fecha, dd, mm, aaaa, codMed2, cantMed2;
    // Imprimir cabecera
    archRep << right << setw(50) << "LISTADO DE CONSULTAS" << endl;
    imprimirLinea(archRep, '=');
    archRep << left << setw(10) << "Paciente" << setw(9) << "Medico"
            << setw(12) << "Fecha" << "Medicinas" << endl;
    imprimirLinea(archRep, '-');
    // Imprimir listado de consultas
    while (true) {
        archCon >> dniPac;
        if (archCon.eof()) break;
        archCon >> codAten >> fecha >> cantMed2;
        dd = fecha % 100;
        mm = (fecha / 100) % 100;
        aaaa = fecha / 10000;
        archRep << setfill('0') << setw(8) << dniPac << "  " << setfill(' ')
                << codAten << "  " << right << setfill('0') << setw(2) << dd
                << '/' << setw(2) << mm << '/' << setw(4) << aaaa << setfill(' ');
        for (int i = 0; i < cantMed2; i++) {
            archCon >> codMed2;
            archRep << setw(7) << codMed2;
        }
        archRep << endl;
    }
}

/* Funciones auxiliares */

fstream abrirArchivo(const char *nomArch, ios::openmode modoArch) {
    fstream arch(nomArch, modoArch);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

int obtenerNumReg(fstream &arch, int tamReg) {
    arch.seekg(0, ios::end);
    int numReg = arch.tellg() / tamReg;
    arch.seekg(0, ios::beg);
    return numReg;
}

void imprimirLinea(fstream &arch, char c) {
    for (int i = 0; i < 80; i++) {
        arch << c;
    }
    arch << endl;
}
