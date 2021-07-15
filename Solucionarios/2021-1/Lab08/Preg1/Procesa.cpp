/*
 * Archivo: Procesa.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:45 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Procesa.h"
using namespace std;

#define MAX_PLACA 8
#define MAX_NOMBRE_CONDUCTOR 50
#define MAX_NOMBRE_INFRACCION 200
#define MAX_GRAVEDAD 10
#define MAX_LINEA_PREG1 40
#define MAX_LINEA_PREG2 80

Procesa::Procesa() {
    cantidad = 0;
}

Procesa::~Procesa() {
    // No es necesario realizar ninguna acción en este destructor.
}

/* Lectura de datos */

void Procesa::lee() {
    ifstream archFaltas = abrirArchivo("RegistroDeFaltas.csv");
    int licencia, infraccion, dd, mm, aaaa, fecha;
    char c, placa[MAX_PLACA];
    while (true) {
        archFaltas >> licencia;
        if (archFaltas.eof()) break;
        archFaltas >> c >> infraccion >> c >> dd >> c >> mm >> c >> aaaa >> c;
        archFaltas.getline(placa, MAX_PLACA);
        // Guardar datos del conductor
        lregistro[cantidad].SetLicencia(licencia);
        guardarNombreConductor();
        // Guardar datos de la falta/infracción
        fecha = 10000*aaaa + 100*mm + dd;
        lregistro[cantidad].guardarFalta(infraccion, fecha, placa);
        buscarDatosInfraccion(infraccion);
        // Actualizar contador de registros
        cantidad++;
    }
}

ifstream Procesa::abrirArchivo(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

void Procesa::guardarNombreConductor() {
    ifstream archConductores = abrirArchivo("Conductores.csv");
    int licencia;
    char nombre[MAX_NOMBRE_CONDUCTOR];
    // Leer línea por línea
    while (true) {
        archConductores >> licencia;
        if (archConductores.eof()) break;
        // Verificar si es la licencia buscada
        if (licencia == lregistro[cantidad].GetLicencia()) {
            archConductores.get();
            archConductores.getline(nombre, MAX_NOMBRE_CONDUCTOR);
            lregistro[cantidad].SetNombre(nombre);
            break;
        } else {
            while (archConductores.get() != '\n');
        }
    }
}

void Procesa::buscarDatosInfraccion(int codInfBuscado) {
    ifstream archInfracciones = abrirArchivo("Infracciones.csv");
    int codInfLeido, indice, puntos, meses;
    char nombre[MAX_NOMBRE_INFRACCION], gravedad[MAX_GRAVEDAD], c;
    double multa, descuento;
    while (true) {
        archInfracciones >> codInfLeido;
        if (archInfracciones.eof()) break;
        if (codInfBuscado == codInfLeido) {
            archInfracciones.get();
            archInfracciones.getline(nombre, MAX_NOMBRE_INFRACCION, ',');
            archInfracciones.getline(gravedad, MAX_GRAVEDAD, ',');
            archInfracciones >> multa >> c;
            buscarDatosAdicionales(archInfracciones, codInfBuscado, descuento,
                    puntos, meses);
            lregistro[cantidad].guardarInfraccion(codInfBuscado, gravedad,
                    multa, descuento, puntos, meses);
        } else {
            while (archInfracciones.get() != '\n');
        }
    }
}

void Procesa::buscarDatosAdicionales(ifstream& archInfracciones, int infraccion,
        double& descuento, int& puntos, int& meses) {
    char c;
    switch (infraccion/100) {
        case 1: // Grave
            archInfracciones >> descuento >> c >> puntos;
            break;
        case 2: // Leve
            archInfracciones >> descuento;
            break;
        case 3: // Muy Grave
            archInfracciones >> puntos >> c >> meses;
            break;
    }
}

/* Impresión del reporte de prueba */

void Procesa::imprime() {
    ofstream archRep = crearArchivo("Reporte.txt");
    archRep << right << fixed << setprecision(2);
    // Imprimir cabecera
    archRep << setw(29) << "REGISTRO DE FALTAS" << endl;
    imprimirLinea(archRep, '=', MAX_LINEA_PREG1);
    archRep << "Licencia" << setw(12) << "Fecha" << setw(14) << "Placa" << endl;
    // Imprimir lista de registros
    for (int i = 0; i < cantidad; i++) {
        archRep << lregistro[i].GetLicencia() << setw(5) << ' ';
        lregistro[i].imprimirFalta(archRep);
    }
}

ofstream Procesa::crearArchivo(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

void Procesa::imprimirLinea(ofstream& arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        arch.put(c);
    }
    arch << endl;
}

/* Pregunta 2 */

void Procesa::consolida() {
    // TODO
}
