/*
 * Archivo: LFalta.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:08 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Infraccion.h"
#include "Leve.h"
#include "Grave.h"
#include "MuyGrave.h"
#include "LFalta.h"
using namespace std;

LFalta::LFalta() {
    lini = nullptr;
    lfin = nullptr;
}

LFalta::~LFalta() {
    class NFalta* ptr;
    while (lini) {
        ptr = lini;
        lini = lini->sig;
        delete ptr;
    }
}

void LFalta::leer(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    class Infraccion* pfalta;
    class Falta* dfalta;
    int licencia, infraccion, dd, mm, aaaa, fecha;
    char c, placa[10];
    // Leer línea por línea
    while (true) {
        arch >> licencia >> c;
        if (arch.eof()) break;
        arch.getline(placa, 10, ',');
        arch >> dd >> c >> mm >> c >> aaaa >> c >> infraccion;
        fecha = 10000*aaaa + 100*mm + dd;
        // Crear los objetos de las faltas
        dfalta = new Falta(licencia, fecha, placa);
        pfalta = leerInfraccion(infraccion);
        // Agregar la falta al arreglo
        agregarFalta(pfalta, dfalta);
    }
}

class Infraccion* LFalta::leerInfraccion(int infraccion) {
    ifstream arch("Infracciones.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Infracciones.csv" << endl;
        exit(1);
    }
    int codInfLeido, puntos, meses;
    char gravedad[15], c;
    double multa, descuento;
    while (true) {
        arch >> codInfLeido >> c;
        if (arch.eof()) break;
        if (codInfLeido == infraccion) {
            while (arch.get() != ','); // Ignorar descripción de la infracción
            arch.getline(gravedad, 20, ',');
            arch >> multa;
            // Leer datos adicionales según la gravedad de la infracción
            switch (infraccion/100) {
                case 2: // Leve
                    arch >> c >> descuento;
                    return new Leve(infraccion, gravedad, multa, descuento);
                case 1: // Grave
                    arch >> c >> descuento >> c >> puntos;
                    return new Grave(infraccion, gravedad, multa, descuento, puntos);
                case 3: // Muy Grave
                    arch >> c >> puntos >> c >> meses;
                    return new MuyGrave(infraccion, gravedad, multa, puntos, meses);
            }
        } else {
            while (arch.get() != '\n');
        }
    }
    return nullptr;
}

void LFalta::agregarFalta(Infraccion* pfalta, Falta* dfalta) {
    // Crear el nodo
    class NFalta* nodo = new NFalta();
    nodo->pfalta = pfalta;
    nodo->dfalta = dfalta;
    // Buscar el sitio donde añadir
    class NFalta *ant = nullptr, *ptr = lini;
    while (ptr) {
        if (ptr->dfalta->GetFecha() > dfalta->GetFecha()) break;
        ant = ptr;
        ptr = ptr->sig;
    }
    // Verificar si se debe agregar al inicio
    if (ant == nullptr) lini = nodo;
    else ant->sig = nodo;
    // Verificar si se debe agregar al final
    if (ptr == nullptr) lfin = nodo;
    else nodo->sig = ptr;
}

void LFalta::unir(const LFalta& lfalta) {
    // El desarrollo de este método se realizará en el proyecto de la pregunta 2.
}

void LFalta::imprimir(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    arch << fixed << setprecision(2);
    class NFalta* ptr = lini;
    while (ptr) {
        ptr->dfalta->imprimir(arch);
        ptr->pfalta->imprimir(arch);
        arch << endl;
        ptr = ptr->sig;
    }
}
