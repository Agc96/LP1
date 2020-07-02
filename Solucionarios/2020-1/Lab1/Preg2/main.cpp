/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "BibliotecaColaGenerica.h"
#include "FuncionesLab1Preg2.h"

int main(int argc, char **argv) {
    void *cola;
    creaCola(cola, leerCliente);
    imprimir(cola, imprimirCliente);
    atiendeCola(cola);
    return 0;
}
