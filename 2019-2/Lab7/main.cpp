/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:11 AM
 */

#include "funciones.h"

int main(int argc, char** argv) {
    void *lpalets, *despachados;
    crealista(lpalets, leerRegistro, comparar);
    imprimelista(lpalets, imprimeRegistro);
    despacha(lpalets, despachados, argc, argv);
    imprimelista(lpalets, imprimeRegistro);
    imprimedespachados(despachados, imprimeRegistro);
    return 0;
}
