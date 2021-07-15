/*
 * Archivo: PriorityQueue.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 11:27 AM
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
using namespace std;

void inicializar(void *&);

void encolar(void *&, void *, void *, int(*)(void *, void *));
void **crearNodo(void *, void *);
void enlazarNodos(void **, void **);

void *desencolar(void *);

bool esVacia(void *);

void prueba(void *, ostream&, void(*)(ostream&, void *, void *));

#endif /* PRIORITYQUEUE_H */
