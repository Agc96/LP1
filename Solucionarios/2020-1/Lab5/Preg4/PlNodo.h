/* 
 * Archivo: PlNodo.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PLNODO_H
#define PLNODO_H

#include "PlCola.h"

template <typename T> class PlCola;

template <typename T> class PlNodo {
public:
    PlNodo();
    friend class PlCola<T>;
private:
    T dato;
    class PlNodo<T>* sig;
};

template <typename T>
PlNodo<T>::PlNodo() {
    sig = nullptr;
}

#endif /* PLNODO_H */
