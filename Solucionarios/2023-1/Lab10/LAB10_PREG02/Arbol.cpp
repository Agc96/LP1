/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:27 AM
 */

#include "Arbol.h"

Arbol::Arbol() {
    raiz = nullptr;
}

Arbol::Arbol(const Arbol& orig) {
}

Arbol::~Arbol() {
    eliminarRecursivo(raiz);
}

void Arbol::eliminarRecursivo(Nodo *nodo) {
    if (nodo->izq) eliminarRecursivo(nodo->izq);
    if (nodo->der) eliminarRecursivo(nodo->der);
    delete nodo;
}

/* Métodos */

void Arbol::insertarAlumno(ifstream &arch, char tipo) {
    // Crear el nuevo nodo
    Nodo *nuevo = new Nodo;
    nuevo->dboleta.leer(arch, tipo);
    // Insertar el nodo ordenadamente
    if (raiz) insertarRecursivo(raiz, nuevo);
    else raiz = nuevo;
}

void Arbol::insertarRecursivo(Nodo *nodo, Nodo *nuevo) {
    if (nodo->dboleta.getCodigo() > nuevo->dboleta.getCodigo()) {
        if (nodo->izq) insertarRecursivo(nodo->izq, nuevo);
        else nodo->izq = nuevo;
    } else {
        if (nodo->der) insertarRecursivo(nodo->der, nuevo);
        else nodo->der = nuevo;
    }
}

void Arbol::insertarEscala(ifstream &arch, int escala) {
    double precio;
    // Leer datos de la escala
    arch.get();
    arch >> precio;
    // Insertar la escala ordenadamente
    lescala[escala-1].SetCodigo(escala);
    lescala[escala-1].SetPrecio(precio);
}

void Arbol::actualizarTotales() {
    actualizarRecursivo(raiz);
}

void Arbol::actualizarRecursivo(Nodo *nodo) {
    int escala;
    double precio;
    // Obtener escala, luego precio, y 
    escala = nodo->dboleta.getEscala();
    precio = lescala[escala-1].GetPrecio();
    nodo->dboleta.actualizar(precio);
    // Realizar lo mismo para los otros
    if (nodo->izq) actualizarRecursivo(nodo->izq);
    if (nodo->der) actualizarRecursivo(nodo->der);
}

void Arbol::imprimir(ofstream &arch) {
    imprimirRecursivo(arch, raiz);
}

void Arbol::imprimirRecursivo(ofstream &arch, Nodo *nodo) {
    if (nodo->izq) imprimirRecursivo(arch, nodo->izq);
    nodo->dboleta.imprimir(arch);
    if (nodo->der) imprimirRecursivo(arch, nodo->der);
}
