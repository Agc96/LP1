/* 
 * Archivo: ListaNotas.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:31 AM
 */

#ifndef LISTANOTAS_H
#define LISTANOTAS_H

#include <fstream>
using namespace std;

class ListaNotas {
public:
    ListaNotas();
    void leer(ifstream&);
    void imprimir(ofstream&);
    virtual ~ListaNotas();
private:
    class NodoNota* lista;
    void insertar(class NodoNota*);
    class NodoNota* crear(char*, int, char*);
};

#endif /* LISTANOTAS_H */
