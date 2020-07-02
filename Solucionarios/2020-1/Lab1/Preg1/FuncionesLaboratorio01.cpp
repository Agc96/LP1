/* 
 * Archivo: FuncionesLaboratorio01.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "BibliotecaColaGenerica.h"
#include "FuncionesLaboratorio01.h"

void *leeNumero(ifstream &arch) {
    int numero, *ptrNum;
    // Leer el número
    arch >> numero;
    if (arch.eof()) {
        return nullptr;
    }
    // Crear el puntero al número
    ptrNum = new int;
    *ptrNum = numero;
    return ptrNum;
}

void imprimeNumero(ofstream &arch, void *dato) {
    int *numero = (int*)dato;
    arch << right << setw(10) << *numero << endl;
}

void atiendeNumero(void *&cola) {
    void **colaAux, *dato;
    int *numero;
    // Abrir el archivo
    ofstream arch("Atencion.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo de atención." << endl;
        exit(1);
    }
    // Desencolar y eliminar los números
    while (!colaVacia(cola)) {
        dato = desencola(cola);
        numero = (int*)dato;
        arch << "Atendiendo numero " << *numero << endl;
        delete numero;
    }
    // Eliminar la cola
    colaAux = (void**)cola;
    delete colaAux;
    cola = nullptr;
}
