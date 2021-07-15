/*
 * Archivo: Reporte.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 10 de octubre de 2020, 05:45 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "BibMedicos.h"
#include "Reporte.h"
using namespace std;

void leerMedicos(StMedico* medicos, int& numMedicos) {
    ifstream arch("Medicos.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Medicos.txt" << endl;
        exit(1);
    }
    // Leer línea por línea
    while (true) {
        arch >> medicos[numMedicos];
        if (arch.eof()) break;
        numMedicos++;
    }
}

void leerPacientes(StMedico* medicos, int numMedicos) {
    ifstream arch("AtencionPacientes.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo AtencionPacientes.txt" << endl;
        exit(1);
    }
    StPaciente paciente;
    int dia, mes, anho;
    char c, codMedico[STMEDICO_MAX_CODIGO];
    // Leer línea por línea
    while (true) {
        arch >> dia >> c >> mes >> c >> anho;
        if (arch.eof()) break;
        paciente.fecha = 10000*anho + 100*mes + dia;
        // Leer cada paciente atendido en la línea
        while (true) {
            arch >> paciente >> codMedico;
            // Buscar el paciente en la lista de médicos
            for (int i = 0; i < numMedicos; i++) {
                if (strcmp(medicos[i].codigo, codMedico) == 0) {
                    medicos[i] + paciente;
                    break;
                }
            }
            // Ver si terminó la línea
            if (arch.peek() == '\n') break;
        }
    }
}

void leerAcciones(StMedico* medicos, int numMedicos) {
    ifstream archAcciones("Acciones.txt", ios::in);
    if (!archAcciones) {
        cerr << "No se pudo abrir el archivo Acciones.txt" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo abrir el archivo Reporte.txt" << endl;
        exit(1);
    }
    int codAccion;
    while (true) {
        archAcciones >> codAccion;
        if (archAcciones.eof()) break;
        switch (codAccion) {
            case 1:
                modificarEstados(medicos, numMedicos, archAcciones);
                break;
            case 2:
                cancelarCitas(medicos, numMedicos, archAcciones);
                break;
            case 3:
                descartarPacientes(medicos, numMedicos, archAcciones);
                break;
            case 4:
                calcularIngresos(medicos, numMedicos, archAcciones);
                break;
            case 5:
                imprimirMedicos(medicos, numMedicos, archAcciones, archReporte);
                break;
        }
    }
}

void modificarEstados(StMedico* medicos, int numMedicos, ifstream& arch) {
    char c, codMedico[STMEDICO_MAX_CODIGO];
    int dia, mes, anho, fecha;
    // Leer el código del médico
    arch >> codMedico;
    // Leer todas las fechas en la línea
    while (true) {
        arch >> dia >> c >> mes >> c >> anho;
        fecha = 10000*anho + 100*mes + dia;
        // Buscar el médico con el código leído
        for (int i = 0; i < numMedicos; i++) {
            if (strcmp(codMedico, medicos[i].codigo) == 0) {
                medicos[i] + fecha;
            }
        }
        // Ver si terminó la línea
        if (arch.peek() == '\n') break;
    }
}

void cancelarCitas(StMedico* medicos, int numMedicos, ifstream& arch) {
    char c, codMedico[STMEDICO_MAX_CODIGO];
    int dia, mes, anho, fecha;
    // Leer el código del médico
    arch >> codMedico;
    // Leer todas las fechas en la línea
    while (true) {
        arch >> dia >> c >> mes >> c >> anho;
        fecha = 10000*anho + 100*mes + dia;
        // Buscar el médico con el código leído
        for (int i = 0; i < numMedicos; i++) {
            if (strcmp(codMedico, medicos[i].codigo) == 0) {
                medicos[i] - fecha;
            }
        }
        // Ver si terminó la línea
        if (arch.peek() == '\n') break;
    }
}

void descartarPacientes(StMedico* medicos, int numMedicos, ifstream& arch) {
    char c, codMedico[STMEDICO_MAX_CODIGO];
    int dia, mes, anho, fecha;
    // Leer el código del médico y la fecha
    arch >> codMedico >> dia >> c >> mes >> c >> anho;
    fecha = 10000*anho + 100*mes + dia;
    // Buscar el médico con el código leído
    for (int i = 0; i < numMedicos; i++) {
        if (strcmp(codMedico, medicos[i].codigo) == 0) {
            medicos[i] / fecha;
        }
    }
}

void calcularIngresos(StMedico* medicos, int numMedicos, ifstream& arch) {
    char codMedico[STMEDICO_MAX_CODIGO];
    // Leer todos los códigos de los médicos en la línea
    while (true) {
        arch >> codMedico;
        // Buscar el médico con el código leído
        for (int i = 0; i < numMedicos; i++) {
            if (strcmp(codMedico, medicos[i].codigo) == 0) {
                ++medicos[i];
            }
        }
        // Ver si terminó la línea
        if (arch.peek() == '\n') break;
    }
}

void imprimirMedicos(StMedico* medicos, int numMedicos, ifstream& archAcciones,
        ofstream& archReporte) {
    char codMedico[STMEDICO_MAX_CODIGO];
    // Leer todos los códigos de los médicos en la línea
    while (true) {
        archAcciones >> codMedico;
        // Buscar el médico con el código leído
        for (int i = 0; i < numMedicos; i++) {
            if (strcmp(codMedico, medicos[i].codigo) == 0) {
                archReporte << medicos[i] << endl;
            }
        }
        // Ver si terminó la línea
        if (archAcciones.peek() == '\n') break;
    }
}
