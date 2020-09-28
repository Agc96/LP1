/* 
 * Archivo: Reserva.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include "Reserva.h"
#include "Sobrecarga.h"
using namespace std;

#define MAX_LINEA 80

void Reserva::carga(const char* nomArchAulas, const char* nomArchMiembros) {
    // Abrir los archivos
    ifstream archAulas(nomArchAulas, ios::in);
    if (!archAulas) {
        cerr << "No se pudo cargar el archivo " << nomArchAulas << endl;
        exit(1);
    }
    ifstream archMiembros(nomArchMiembros, ios::in);
    if (!archMiembros) {
        cerr << "No se pudo cargar el archivo " << nomArchMiembros << endl;
        exit(1);
    }
    // Realizar las cargas
    cargaAulas(archAulas);
    cargaMiembros(archMiembros);
}

void Reserva::cargaAulas(istream& arch) {
    Aula aula;
    // Leer línea por línea
    while (true) {
        arch >> aula;
        if (arch.eof()) break;
        vAula.push_back(aula);
    }
}

void Reserva::cargaMiembros(istream& arch) {
    Alumno alumno;
    Profesor profesor;
    char tipo, c;
    // Leer línea por línea
    while (true) {
        arch >> tipo >> c;
        if (arch.eof()) break;
        // Encolar persona según su tipo
        if (tipo == 'A') {
            arch >> alumno;
            alumnos.encolar(alumno);
        } else if (tipo == 'P') {
            arch >> profesor;
            profesores.encolar(profesor);
        }
    }
}

void Reserva::asigna(int capMaxima) {
    Persona persona;
    char tipo, *nombre;
    // Asignar todas las aulas según su capacidad
    for (vector<Aula>::iterator it = vAula.begin(); it != vAula.end(); ++it) {
        if (it->getCapacidad() <= capMaxima) {
            if (alumnos.estaVacia()) continue;
            persona = alumnos.desencolar();
            tipo = 'A';
        } else {
            if (profesores.estaVacia()) continue;
            persona = profesores.desencolar();
            tipo = 'P';
        }
        // Colocar el código de la persona
        it->setCodigo(persona.GetCodigo());
        // Colocar el nombre de la persona
        nombre = persona.GetNombre();
        it->setNombre(nombre);
        delete nombre;
        // Colocar el tipo de la persona
        it->setTipo(tipo);
    }
}

void Reserva::imprime(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    // Imprimir la lista de aulas
    arch << setw(50) << "Reservas asignadas" << endl;
    for (vector<Aula>::iterator it = vAula.begin(); it != vAula.end(); ++it) {
        arch << *it;
        separacion(arch, '-', MAX_LINEA);
    }
}

/* Funciones auxiliares */

void Reserva::separacion(ostream& out, char c, int max) {
    for (int i = 0; i < max; i++) {
        out.put(c);
    }
    out << endl;
}
