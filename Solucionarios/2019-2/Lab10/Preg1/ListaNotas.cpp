/* 
 * Archivo: ListaNotas.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:31 AM
 */

#include "ListaNotas.h"
#include "NodoNota.h"
#include "Nota.h"

#include <cstring>
using namespace std;

#define MAX_LINEA 100

ListaNotas::ListaNotas() {
}

void ListaNotas::leer(ifstream& archivo) {
    char codigo[MAX_LINEA], semestre[MAX_LINEA], c;
    int nota;
    class NodoNota* nodo;
    // Leer todo el archivo
    while (true) {
        // Leer código
        archivo.getline(codigo, MAX_LINEA, ',');
        if (archivo.eof()) break;
        // Leer nota obtenida
        archivo >> c >> nota;
        // Leer semestre
        archivo.getline(semestre, MAX_LINEA, ',');
        // Preparar nodo e insertarlo ordenadamente
        nodo = crear(codigo, nota, semestre);
        insertar(nodo);
    }
}

void ListaNotas::insertar(class NodoNota* nodo) {
    class NodoNota *nodoActual = lista, *nodoAnterior = nullptr;
    if (lista) {
        // Buscar dónde insertar ordenadamente
        while (nodoActual) {
            // Determinar si el nodo actual
            int resultado = nodoActual->comparar(nodo);
            // Actualizar los datos
            if (resultado == 0) {
                nodoActual->actualizar(nodo);
                return;
            }
            if (resultado > 0) {
                // Actualizar estructura de la lista
                nodoAnterior->sig = nodo;
                nodo->sig = nodoActual;
                return;
            }
            // Ir al siguiente nodo
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sig;
        }
    } else {
        lista = nodo;
    }
}

class NodoNota* ListaNotas::crear(char* codigo, int nota, char* semestre) {
    class NodoNota* nodo = new NodoNota;
    nodo->nota.setCodigo(codigo);
    nodo->nota.setNota(nota);
    nodo->nota.setSemestre(semestre);
    return nodo;
}

void ListaNotas::imprimir(ofstream& archivo) {
    // TODO
}

ListaNotas::~ListaNotas() {
}
