/*
 * Archivo: Registro.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:53 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Registro.h"
using namespace std;

Registro::Registro() {
    // No es necesario realizar ninguna acción en este constructor.
}

Registro::~Registro() {
    // No es necesario realizar ninguna acción en este destructor.
}

void Registro::guardarFalta(int infraccion, int fecha, const char* placa) {
    switch (infraccion/100) {
        case 1: // Grave
            lgrave.SetCodigo(infraccion);
            lgrave.SetFecha(fecha);
            lgrave.SetPlaca(placa);
            break;
        case 2: // Leve
            lleve.SetCodigo(infraccion);
            lleve.SetFecha(fecha);
            lleve.SetPlaca(placa);
            break;
        case 3: // Muy Grave
            lmgrave.SetCodigo(infraccion);
            lmgrave.SetFecha(fecha);
            lmgrave.SetPlaca(placa);
            break;
    }
}

void Registro::guardarInfraccion(int infraccion, const char* gravedad,
        double multa, double descuento, int puntos, int meses) {
    switch (infraccion/100) {
        case 1: // Grave
            lgrave.SetGravedad(gravedad);
            lgrave.SetMulta(multa);
            lgrave.SetDescuento(descuento);
            lgrave.SetPuntos(puntos);
            break;
        case 2: // Leve
            lleve.SetGravedad(gravedad);
            lleve.SetMulta(multa);
            lleve.SetDescuento(descuento);
            break;
        case 3: // Muy Grave
            lmgrave.SetGravedad(gravedad);
            lmgrave.SetMulta(multa);
            lmgrave.SetPuntos(puntos);
            lmgrave.SetMeses(meses);
            break;
    }
}

void Registro::imprimirFalta(ofstream& arch) {
    if (lleve.GetCodigo() != 0) {
        imprimirDatosFalta(arch, lleve.GetFecha(), lleve.GetPlaca());
    }
    if (lgrave.GetCodigo() != 0) {
        imprimirDatosFalta(arch, lgrave.GetFecha(), lgrave.GetPlaca());
    }
    if (lmgrave.GetCodigo() != 0) {
        imprimirDatosFalta(arch, lmgrave.GetFecha(), lmgrave.GetPlaca());
    }
}

void Registro::imprimirDatosFalta(ofstream& arch, int fecha, char* placa) {
    // Imprimir fecha
    arch << setfill('0') << setw(2) << (fecha%100) << '/';
    arch << setw(2) << ((fecha/100)%100) << '/';
    arch << setw(4) << (fecha/10000) << setfill(' ');
    // Imprimir placa
    arch << setw(5) << ' ' << placa << endl;
    delete placa;
}
