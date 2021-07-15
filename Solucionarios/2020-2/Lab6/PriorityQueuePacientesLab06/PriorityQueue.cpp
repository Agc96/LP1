/*
 * Archivo: PriorityQueue.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 11:27 AM
 */

#include "PriorityQueue.h"

enum posCola{POS_INI, POS_FIN};
enum posNodo{POS_DATO, POS_ANT, POS_SIG};
enum posDato{POS_PRIORIDAD, POS_VALOR};

void encolar(void *&ptCola, void *prioridad, void *valor, int(*fnComparacion)(void *, void *)) {
    // Crear el nodo del dato
    void **nodoNuevo = crearNodo(prioridad, valor);
    // Verificar si la cola está vacía
    void **cola = (void**)ptCola;
    if (esVacia(ptCola)) {
        cola[POS_INI] = cola[POS_FIN] = nodoNuevo;
        return;
    }
    // Recorrer la cola desde atrás y buscar dónde insertar el nodo
    void **nodoAnt = (void**)(cola[POS_FIN]);
    void **nodoSig, **datoAnt, *prioridadAnt;
    while (nodoAnt != nullptr) {
        datoAnt = (void **)(nodoAnt[POS_DATO]);
        prioridadAnt = datoAnt[POS_PRIORIDAD];
        if (fnComparacion(prioridad, prioridadAnt) <= 0) {
            // Ver si existe un nodo siguiente al anterior
            nodoSig = (void **)(nodoAnt[POS_SIG]);
            if (nodoSig != nullptr) {
                // Insertar en la mitad de la cola
                enlazarNodos(nodoSig, nodoNuevo);
            } else {
                // Insertar al final de la cola
                cola[POS_FIN] = nodoNuevo;
            }
            enlazarNodos(nodoNuevo, nodoAnt);
            return;
        }
        nodoAnt = (void**)(nodoAnt[POS_ANT]);
    }
    // Si no se pudo insertar antes, insertar al inicio de la cola
    void** nodoInicio = (void**)(cola[POS_INI]);
    enlazarNodos(nodoInicio, nodoNuevo);
    cola[POS_INI] = nodoNuevo;
}

void inicializar(void*& ptCola) {
    void** cola = new void*[2];
    cola[POS_INI] = nullptr;
    cola[POS_FIN] = nullptr;
    ptCola = cola;
}

void** crearNodo(void* prioridad, void* valor) {
    // Crear el nodo del dato
    void** dato = new void*[2];
    dato[POS_PRIORIDAD] = prioridad;
    dato[POS_VALOR] = valor;
    // Crear el nodo de la cola
    void** nodo = new void*[3];
    nodo[POS_DATO] = dato;
    nodo[POS_ANT] = nullptr;
    nodo[POS_SIG] = nullptr;
    return nodo;
}

void enlazarNodos(void **nodoActual, void **nodoAnterior) {
    nodoActual[POS_ANT] = nodoAnterior;
    nodoAnterior[POS_SIG] = nodoActual;
}

void* desencolar(void *ptCola, void(*fnEliminar)(void *)) {
    // Verificar que la cola no esté vacía
    if (esVacia(ptCola)) return nullptr;
    // Obtener el dato a desencolar
    void **cola = (void **)ptCola;
    void **nodo = (void **)(cola[POS_INI]);
    void **dato = (void **)(nodo[POS_DATO]);
    void *valor = dato[POS_VALOR];
    // Eliminar el nodo del inicio de la cola
    void** nodoSig = (void**)(nodo[POS_SIG]);
    if (nodoSig != nullptr) {
        nodoSig[POS_ANT] = nullptr;
    }
    cola[POS_INI] = nodoSig;
    // Eliminar los punteros que ya no se utilizarán
    delete nodo;
    fnEliminar(dato[POS_PRIORIDAD]);
    delete dato;
    // Entregar un puntero al dato
    return valor;
}

bool esVacia(void* ptCola) {
    // Verificar si la cola existe
    if (ptCola == nullptr) return true;
    // Verificar si los nodos existen
    void** cola = (void**)ptCola;
    return (cola[POS_INI] == nullptr) || (cola[POS_FIN] == nullptr);
}

void prueba(void* ptCola, ostream &out, void(*fnImprimir)(ostream &, void *, void *)) {
    // Verificar si la cola está vacía
    if (esVacia(ptCola)) {
        out << "Cola de prioridad vacia" << endl;
        return;
    }
    // Imprimir todos los datos de la cola
    void **cola = (void **)ptCola;
    void **nodo = (void **)(cola[POS_INI]), **dato;
    while (nodo != nullptr) {
        dato = (void **)(nodo[POS_DATO]);
        fnImprimir(out, dato[POS_PRIORIDAD], dato[POS_VALOR]);
        nodo = (void **)(nodo[POS_SIG]);
    }
}
