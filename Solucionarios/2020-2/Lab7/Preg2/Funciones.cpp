/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Paciente.h"
#include "Medico.h"
#include "Funciones.h"
using namespace std;

#define MAX_CODIGO 7
#define NO_ENCONTRADO -1

void leerMedicos(Medico* medicos, int& numMedicos) {
    ifstream arch = abrirArchivo("Medicos.txt");
    numMedicos = 0;
    while (true) {
        arch >> medicos[numMedicos];
        if (arch.eof()) break;
        numMedicos++;
    }
}

void leerPacientes(Medico* medicos, int numMedicos) {
    ifstream arch = abrirArchivo("AtencionPacientes.txt");
    int dia, mes, anho, pos;
    char codMedico[MAX_CODIGO], c;
    Paciente paciente;
    // Leer línea por línea
    while (true) {
        arch >> dia;
        if (arch.eof()) break;
        if (arch.fail()) {
            arch.clear();
            // Leer datos del paciente y buscar 
            arch >> paciente >> codMedico;
            pos = buscarMedico(medicos, numMedicos, codMedico);
            if (pos != NO_ENCONTRADO) {
                medicos[pos] + paciente;
            }
        } else {
            // Leer fecha de atención
            arch >> c >> mes >> c >> anho;
            paciente.setFecha(10000*anho + 100*mes + dia);
        }
    }
}

int buscarMedico(Medico* medicos, int numMedicos, char* codBuscado) {
    char* codMedico;
    int resultado;
    for (int i = 0; i < numMedicos; i++) {
        codMedico = medicos[i].getCodigo();
        resultado = strcmp(codBuscado, codMedico);
        delete codMedico;
        if (resultado == 0) return i;
    }
    return NO_ENCONTRADO;
}

void leerAcciones(Medico* medicos, int numMedicos) {
    ifstream archAcc = abrirArchivo("Acciones.txt");
    ofstream archRep = crearArchivo("Reporte.txt");
    int accion;
    // Leer línea por línea
    while (true) {
        archAcc >> accion;
        if (archAcc.eof()) break;
        switch (accion) {
            case 1:
                modificarEstados(medicos, numMedicos, archAcc);
                break;
            case 2:
                cancelarCitas(medicos, numMedicos, archAcc);
                break;
            case 3:
                calcularIngresos(medicos, numMedicos, archAcc);
                break;
            case 4:
                imprimirMedico(medicos, numMedicos, archAcc, archRep);
                break;
        }
    }
}

void modificarEstados(Medico* medicos, int numMedicos, ifstream& arch) {
    char codMedico[MAX_CODIGO], c;
    int dia, mes, anho, fecha, pos;
    // Leer el código del médico
    arch >> ws >> codMedico;
    pos = buscarMedico(medicos, numMedicos, codMedico);
    // Leer fechas hasta llegar al fin de línea
    while (true) {
        arch >> dia >> c >> mes >> c >> anho;
        fecha = 10000*anho + 100*mes + dia;
        if (pos != NO_ENCONTRADO) {
            medicos[pos] * fecha;
        }
        if (arch.peek() == '\n') break;
    }
}

void cancelarCitas(Medico* medicos, int numMedicos, ifstream& arch) {
    char codMedico[MAX_CODIGO], c;
    int dia, mes, anho, fecha, pos;
    // Leer el código del médico
    arch >> ws >> codMedico;
    pos = buscarMedico(medicos, numMedicos, codMedico);
    // Leer fechas hasta llegar al fin de línea
    while (true) {
        arch >> dia >> c >> mes >> c >> anho;
        fecha = 10000*anho + 100*mes + dia;
        if (pos != NO_ENCONTRADO) {
            medicos[pos] - fecha;
        }
        if (arch.peek() == '\n') break;
    }
}

void calcularIngresos(Medico* medicos, int numMedicos, ifstream& arch) {
    char codMedico[MAX_CODIGO];
    int pos;
    // Leer médicos hasta llegar al fin de línea
    while (true) {
        arch >> ws >> codMedico;
        pos = buscarMedico(medicos, numMedicos, codMedico);
        if (pos != NO_ENCONTRADO) {
            ++medicos[pos];
        }
        if (arch.peek() == '\n') break;
    }
}

void imprimirMedico(Medico* medicos, int numMedicos, ifstream& archAcc,
        ofstream& archRep) {
    char codMedico[MAX_CODIGO];
    int pos;
    // Leer médicos hasta llegar al fin de línea
    while (true) {
        archAcc >> ws >> codMedico;
        pos = buscarMedico(medicos, numMedicos, codMedico);
        if (pos != NO_ENCONTRADO) {
            archRep << medicos[pos] << endl;
        }
        if (archAcc.peek() == '\n') break;
    }
}

/* Funciones auxiliares */

ifstream abrirArchivo(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream crearArchivo(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}
