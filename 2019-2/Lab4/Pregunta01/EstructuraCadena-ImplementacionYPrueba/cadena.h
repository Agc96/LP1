/* 
 * Archivo: cadena.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 12:43 PM
 */

#ifndef CADENA_H
#define CADENA_H

#include <fstream>
#define MAX_CADENA 100
using namespace std;

struct Cadena {
    char cadena[MAX_CADENA];
    int longitud = 0;
    bool overF = false;
};

void inicializa(Cadena&, char, int = MAX_CADENA);
void inicializa(Cadena&);
void leer(ifstream&, Cadena&, char = '\n');
void imprimir(ofstream&, Cadena&);
int longitud(Cadena&);
void recortar(Cadena&);
void intercambiar(Cadena&, Cadena&);

Cadena& operator &(Cadena&, Cadena&);
Cadena& operator +=(Cadena&, const Cadena&);
Cadena operator +(const Cadena&, const Cadena&);
bool operator ==(const Cadena&, const Cadena&);
bool operator <(const Cadena&, const Cadena&);
bool operator >(const Cadena&, const Cadena&);
ifstream& operator >>(ifstream&, Cadena&);
ofstream& operator <<(ofstream&, Cadena&);

#endif /* CADENA_H */
