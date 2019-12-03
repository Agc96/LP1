/* 
 * Archivo: NodoNota.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:35 AM
 */

#ifndef NODONOTA_H
#define NODONOTA_H

#include "ListaNotas.h"
#include "Nota.h"

class NodoNota {
public:
    NodoNota();
    virtual ~NodoNota();
    bool comparar(NodoNota* nodo);
    void actualizar(NodoNota* nodo);
    friend class ListaNotas;
private:
    class Nota nota;
    class NodoNota* sig;
};

#endif /* NODONOTA_H */
