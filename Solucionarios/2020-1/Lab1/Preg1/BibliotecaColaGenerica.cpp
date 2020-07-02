/* 
 * Archivo: BibliotecaColaGenerica.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "BibliotecaColaGenerica.h"

void creaCola(void *&cola, void *(*funcLeer)(ifstream &)) {
    void **colaAux, *dato;
    // Abrir el archivo
    ifstream arch("Numeros.txt", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo para crear la cola." << endl;
        exit(1);
    }
    // Crear la cola
    colaAux = new void*[2];
    colaAux[0] = nullptr;
    colaAux[1] = nullptr;
    cola = colaAux;
    // Leer el archivo
    while (true) {
        dato = funcLeer(arch);
        if (dato == nullptr) break;
        encola(cola, dato);
    }
}

void encola(void *cola, void *dato) {
    void **colaAux, **regNuevo, **regAnterior;
    // Crear el registro donde se almacenará el dato
    regNuevo = new void*[2];
    regNuevo[0] = dato;
    regNuevo[1] = nullptr;
    // Colocar el registro en la cola
    colaAux = (void**)cola;
    if (colaVacia(cola)) {
        colaAux[0] = regNuevo;
    } else {
        regAnterior = (void**)(colaAux[1]);
        regAnterior[1] = regNuevo;
    }
    // Reemplazar el final de la cola
    colaAux[1] = regNuevo;
}

void *desencola(void *cola) {
    void **colaAux, **regInicio, *dato;
    // Ver si la cola está vacía
    if (colaVacia(cola)) {
        return nullptr;
    } else {
        // Obtener el dato del registro
        colaAux = (void**)cola;
        regInicio = (void**)(colaAux[0]);
        dato = regInicio[0];
        // Reemplazar el inicio de la cola
        colaAux[0] = regInicio[1];
        delete regInicio;
        // Devolver el dato contenido en el registro
        return dato;
    }
}

void imprimir(void *cola, void (*funcImprimir)(ofstream &, void *)) {
    void **colaAux, **reg;
    // Abrir el archivo
    ofstream arch("Reporte.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo para imprimir la cola." << endl;
        exit(1);
    }
    // Imprimir cabecera
    arch << "Impresión de la cola" << endl;
    arch << "====================" << endl;
    // Obtener el primer registro de la cola
    if (colaVacia(cola)) {
        arch << "[Cola vacía]" << endl;
    } else {
        colaAux = (void**)cola;
        reg = (void**)(colaAux[0]);
        while (reg != nullptr) {
            funcImprimir(arch, reg[0]);
            reg = (void**)(reg[1]);
        }
    }
}

bool colaVacia(void *cola) {
    void **colaAux = (void**)cola;
    return colaAux[0] == nullptr || colaAux[1] == nullptr;
}
