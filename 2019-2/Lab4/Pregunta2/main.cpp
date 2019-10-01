/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 30 de septiembre de 2019, 03:07 PM
 */

#include <iostream>
#include "funciones.h"
using namespace std;

int main(int argc, char** argv) {
    Cadena codigos[MAX_CURSOS], cursos[MAX_CURSOS], especialidades[MAX_CURSOS];
    double creditos[MAX_CURSOS];
    
    int numRegistros = leerArchivos(codigos, cursos, especialidades, creditos);
    ordenarDatos(codigos, cursos, especialidades, creditos, 0, numRegistros - 1);
    imprimirReporte(codigos, cursos, especialidades, creditos, numRegistros);
    return 0;
}
