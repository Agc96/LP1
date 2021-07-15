/*
 * Archivo: ListaPacientes.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "ListaPacientes.h"
#include "Paciente.h"
#include "Ambulatorio.h"
#include "Urgencia.h"
#include "Emergencia.h"
using namespace std;

ListaPacientes::ListaPacientes() {
    inicio = nullptr;
}

ListaPacientes::~ListaPacientes() {
    NodoPaciente* aux;
    while (inicio) {
        aux = inicio;
        inicio = inicio->sig;
        delete aux;
    }
}

/* Métodos */

void ListaPacientes::creaLista(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    Paciente* pac;
    char tipo, c;
    while (true) {
        arch >> tipo >> c;
        if (arch.eof()) break;
        switch (tipo) {
            case 'A':
                pac = new Ambulatorio();
                break;
            case 'U':
                pac = new Urgencia();
                break;
            case 'E':
                pac = new Emergencia();
                break;
        }
        pac->leer(arch);
        agregarPaciente(pac);
    }
}

void ListaPacientes::agregarPaciente(class Paciente* pac) {
    // Crear el nodo del paciente
    NodoPaciente *nuevo = new NodoPaciente(pac);
    // Agregar el nodo al final de la lista
    NodoPaciente *aux = inicio, *ant = nullptr;
    while (aux) {
        if (aux->pac->orden() > nuevo->pac->orden()) break;
        ant = aux;
        aux = aux->sig;
    }
    nuevo->sig = aux;
    if (ant) ant->sig = nuevo;
    else inicio = nuevo;
}

void ListaPacientes::imprimeLista(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    // Imprimir cabecera del resumen
    arch << fixed << setprecision(2);
    arch << right << setw(74) << "INSTITUTO DE SALUD SA" << endl;
    separacion(arch, '=');
    // Imprimir pacientes según el tipo
    for (int i = 1; i <= 3; i++) {
        imprimeCabeceraSeccion(arch, i);
        separacion(arch, '-');
        imprimeCabeceraPacientes(arch, i);
        imprimePacientes(arch, i);
        separacion(arch, '=');
    }
    // Imprimir cantidad de pacientes atendidos por seguro
    arch << "Atendidos por seguro: " << contarSeguro() << " pacientes" << endl;
}

void ListaPacientes::imprimeCabeceraSeccion(ostream& arch, int orden) {
    switch (orden) {
        case 1:
            arch << setw(84) << "PACIENTES ATENDIDOS DE MANERA AMBULATORIA" << endl;
            break;
        case 2:
            arch << setw(80) << "PACIENTES ATENDIDOS POR URGENCIA" << endl;
            break;
        case 3:
            arch << setw(81) << "PACIENTES ATENDIDOS POR EMERGENCIA" << endl;
            break;
    }
}

void ListaPacientes::imprimeCabeceraPacientes(ostream& arch, int orden) {
    arch << left << setw(8) << "No." << setw(12) << "Codigo";
    arch << setw(50) << "Nombre" << right << setw(10) << "Medico";
    switch (orden) {
        case 1:
            arch << setw(14) << "% por Seg." << endl;
            break;
        case 2:
            arch << setw(14) << "% por Seg." << setw(14) << "% Urgencia" << endl;
            break;
        case 3:
            arch << setw(30) << "Referencia" << endl;
            break;
    }
}

void ListaPacientes::imprimePacientes(ostream& arch, int orden) {
    NodoPaciente* aux = inicio;
    Paciente* pac;
    int conteo = 0;
    while (aux) {
        pac = aux->pac;
        if (pac->orden() == orden) {
            conteo++;
            arch << setw(3) << conteo << ')' << setw(4) << ' ';
            pac->imprimir(arch);
        }
        aux = aux->sig;
    }
}

void ListaPacientes::separacion(ostream& arch, char c) {
    for (int i = 0; i < 128; i++)
        arch.put(c);
    arch << endl;
}

int ListaPacientes::contarSeguro() {
    NodoPaciente* aux = inicio;
    int seguro = 0;
    while (aux) {
        if (aux->pac->seguro())
            seguro++;
        aux = aux->sig;
    }
    return seguro;
}
