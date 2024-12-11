/*
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de septiembre de 2022, 12:00 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

void inicializarArchBin() {
    fstream archPac = abrirArchivo("Pacientes.bin", ios::in | ios::out | ios::binary);
    int tamReg, numReg;
    double gasto = 0;
    tamReg = sizeof(int) + sizeof(char)*20 + sizeof(double);
    numReg = obtenerNumReg(archPac, tamReg);
    for (int i = 0; i < numReg; i++) {
        archPac.seekg((i+1)*tamReg - sizeof(double), ios::beg);
        archPac.read(reinterpret_cast<char*>(&gasto), sizeof(double));
    }
}

void completaBinarioPacientes() {
    fstream archCon = abrirArchivo("Consultas.txt", ios::in);
    int dniPac, fecha, cantMed2, codMed2;
    char codAten[8];
    double precio;
    while (true) {
        archCon >> dniPac;
        if (archCon.eof()) break;
        archCon >> codAten >> fecha >> cantMed2;
        for (int i = 0; i < cantMed2; i++) {
            archCon >> codMed2;
            precio = buscarPrecioMedicina(codMed2);
            actualizarPaciente(dniPac, precio);
        }
    }
}

double buscarPrecioMedicina(int codBuscado) {
    fstream archMed = abrirArchivo("Medicinas.bin", ios::in | ios::binary);
    int codLeido, tamReg, numReg;
    double precio;
    tamReg = sizeof(int) + sizeof(char)*40 + sizeof(double);
    numReg = obtenerNumReg(archMed, tamReg);
    for (int i = 0; i < numReg; i++) {
        archMed.seekg(i*tamReg, ios::beg);
        archMed.read(reinterpret_cast<char*>(&codLeido), sizeof(int));
        if (codBuscado == codLeido) {
            archMed.seekg((i+1)*tamReg - sizeof(double), ios::beg);
            archMed.read(reinterpret_cast<char*>(&precio), sizeof(double));
            return precio;
        }
    }
    return 0;
}

void actualizarPaciente(int dniBuscado, double precio) {
    fstream archPac = abrirArchivo("Pacientes.bin", ios::in | ios::out | ios::binary);
    int dniLeido, tamReg, numReg;
    double gasto;
    tamReg = sizeof(int) + sizeof(char)*20 + sizeof(double);
    numReg = obtenerNumReg(archPac, tamReg);
    for (int i = 0; i < numReg; i++) {
        archPac.seekg(i*tamReg, ios::beg);
        archPac.read(reinterpret_cast<char*>(&dniLeido), sizeof(int));
        if (dniBuscado == dniLeido) {
            archPac.seekg((i+1)*tamReg - sizeof(double), ios::beg);
            archPac.read(reinterpret_cast<char*>(&gasto), sizeof(double));
            gasto += precio;
            archPac.seekg((i+1)*tamReg - sizeof(double), ios::beg);
            archPac.write(reinterpret_cast<const char*>(&gasto), sizeof(double));
            break;
        }
    }
}

void reporteFinal() {
    fstream archRep = abrirArchivo("Reporte.txt", ios::out);
    archRep << fixed << setprecision(2);
    // Imprimir cabecera
    archRep << setw(77) << "EMPRESA PRESTADORA DE SALUD EPS-LP1" << endl;
    imprimirLinea(archRep, '=');
    // Imprimir listados
    reporteMedicos(archRep);
    reportePacientes(archRep);
    reporteMedicinas(archRep);
    reporteConsultas(archRep);
}

void reporteMedicos(fstream &archRep) {
    fstream archMed = abrirArchivo("Medicos.txt", ios::in);
    char codMed[8], nomMed[40], especMed[20];
    int indice = 1;
    // Imprimir cabecera
    archRep << setw(68) << "STAFF DE MEDICOS" << endl;
    archRep << left << setw(25) << ' ' << setw(10) << "CODIGO"
            << setw(40) << "NOMBRE" << "ESPECIALIDAD" << endl;
    // Imprimir listado de médicos
    while (true) {
        archMed >> codMed >> nomMed >> especMed;
        if (archMed.eof()) break;
        formatearNombre(nomMed);
        archRep << right << setw(22) << indice << ")  " << left << setw(10)
                << codMed << setw(40) << nomMed << especMed << endl;
        indice++;
    }
    imprimirLinea(archRep, '=');
}

void reportePacientes(fstream &archRep) {
    fstream archPac = abrirArchivo("Pacientes.bin", ios::in | ios::binary);
    int dniPac, indice = 1;
    char nomPac[20];
    double gasto;
    // Imprimir cabecera
    archRep << right << setw(70) << "PACIENTES REGISTRADOS" << endl;
    archRep << left << setw(25) << ' ' << setw(10) << "DNI"
            << setw(30) << "NOMBRE" << "GASTOS POR MEDICINAS" << endl;
    // Imprimir listado de pacientes
    while (true) {
        archPac.read(reinterpret_cast<char*>(&dniPac), sizeof(int));
        if (archPac.eof()) break;
        archPac.read(reinterpret_cast<char*>(nomPac), sizeof(char)*20);
        archPac.read(reinterpret_cast<char*>(&gasto), sizeof(double));
        formatearNombre(nomPac); // Opcional
        archRep << right << setw(22) << indice << ")  " 
                << setfill('0') << setw(8) << dniPac << "  " << setfill(' ')
                << left << setw(30) << nomPac
                << right << setw(16) << gasto << endl;
        indice++;
    }
    imprimirLinea(archRep, '=');
}

void reporteMedicinas(fstream &archRep) {
    fstream archMed = abrirArchivo("Medicinas.bin", ios::in | ios::binary);
    int codMed2, indice = 1;
    char descMed2[40];
    double precMed2;
    // Imprimir cabecera
    archRep << right << setw(69) << "MEDICINAS EN STOCK" << endl;
    archRep << left << setw(25) << ' ' << setw(10) << "CODIGO"
            << setw(40) << "DESCRIPCION" << "PRECIO" << endl;
    // Imprimir listado de medicinas
    while (true) {
        archMed.read(reinterpret_cast<char*>(&codMed2), sizeof(int));
        if (archMed.eof()) break;
        archMed.read(reinterpret_cast<char*>(descMed2), sizeof(char)*40);
        archMed.read(reinterpret_cast<char*>(&precMed2), sizeof(double));
        formatearNombre(descMed2); // Opcional
        archRep << right << setw(22) << indice << ")  "
                << left << setw(10) << codMed2 << setw(40) << descMed2
                << right << setw(6) << precMed2 << endl;
        indice++;
    }
    imprimirLinea(archRep, '=');
}

void reporteConsultas(fstream &archRep) {
    fstream archCon = abrirArchivo("Consultas.txt", ios::in);
    int dniPac, fecha, codMed2, cantMed2, indice = 1;
    char codAten[8], espec[20] = "A";
    // Imprimir cabecera
    archRep << right << setw(70) << "RELACION DE CONSULTAS" << endl;
    archRep << left << setw(6) << ' ' << setw(10) << "PACIENTE"
            << setw(9) << "MEDICO" << setw(20) << "ESPECIALIDAD"
            << setw(12) << "FECHA" << setw(25) << "CANTIDAD DE MEDICINAS"
            << "CODIGOS DE MEDICAMENTOS" << endl;
    // Imprimir listado de consultas
    while (true) {
        archCon >> dniPac;
        if (archCon.eof()) break;
        archCon >> codAten >> fecha >> cantMed2;
        obtenerEspecialidad(codAten, espec);
        archRep << right << setw(3) << indice << ")  "
                << setfill('0') << setw(8) << dniPac << "  " << setfill(' ')
                << left << setw(9) << codAten << setw(20) << espec;
        imprimirFecha(archRep, fecha);
        archRep << setw(15) << cantMed2 << setw(10) << ' ';
        for (int i = 0; i < cantMed2; i++) {
            archCon >> codMed2;
            archRep << setw(7) << codMed2;
        }
        archRep << endl;
        indice++;
    }
}

void obtenerEspecialidad(char *codBuscado, char *espec) {
    fstream archMed = abrirArchivo("Medicos.txt", ios::in);
    char codLeido[8], nomMed[40];
    while (true) {
        archMed >> codLeido >> nomMed >> espec;
        if (archMed.eof()) break;
        if (strcmp(codBuscado, codLeido) == 0) return;
    }
    strcpy(espec, "No encontrado");
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

void formatearNombre(char *nombre) {
    for (int i = 0; i < strlen(nombre); i++) {
        if (nombre[i] == '_' || nombre[i] == '/') nombre[i] = ' ';
    }
}

void imprimirFecha(fstream &archRep, int fecha) {
    int dd, mm, aaaa;
    dd = fecha % 100;
    mm = (fecha / 100) % 100;
    aaaa = fecha / 10000;
    archRep << right << setfill('0') << setw(2) << dd << '/' << setw(2) << mm
            << '/' << setw(4) << aaaa << setfill(' ');
}

void imprimirLinea(fstream &arch, char c) {
    for (int i = 0; i < 120; i++) {
        arch << c;
    }
    arch << endl;
}
