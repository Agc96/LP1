/* 
 * Archivo: NodoNota.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:35 AM
 */

#include "NodoNota.h"
#include <cstring>
using namespace std;

NodoNota::NodoNota() {
    sig = nullptr;
}

NodoNota::~NodoNota() {
    if (sig) delete sig;
}

bool NodoNota::comparar(NodoNota* nodo) {
    char* codigoIzq = this->nota.getCodigo();
    char* codigoDer = nodo->nota.getCodigo();
    int resultado = strcmp(codigoIzq, codigoDer);
    delete[] codigoIzq;
    delete[] codigoDer;
    return resultado;
}

void NodoNota::actualizar(NodoNota* nodo) {
    nota.setNota(nodo->nota.getNota());
    nota.setSemestre(nodo->nota.getSemestre());
}
