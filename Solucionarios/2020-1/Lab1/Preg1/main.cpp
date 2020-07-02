/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "BibliotecaColaGenerica.h"
#include "FuncionesLaboratorio01.h"

int main() {
    void *cola;
    creaCola(cola, leeNumero);
    imprimir(cola, imprimeNumero);
    atiendeNumero(cola);
    return 0;
}
