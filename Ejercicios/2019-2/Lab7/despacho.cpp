/* 
 * Archivo: despacho.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:24 AM
 */

#include "funciones.h"

void despacha(void*& lista, void*& despachados, int argc, char** argv) {
    // Verificar la cantidad de argumentos (2 * pareja + nombre del archivo)
    if (argc % 2 != 1) {
        cerr << "Debe ingresar parejas de producto y cantidad en los argumentos." << endl;
        exit(1);
    }
    // Abrir archivo de productos faltantes (salida)
    ofstream archivo("files/Faltantes.txt", ios::out);
    if (!archivo) {
        cerr << "No se pudo crear el archivo de productos faltantes." << endl;
        exit(1);
    }
    // Despachar cada pareja de datos
    despachados = NULL;
    for (int i = 1; i < argc; i += 2) {
        char* codProducto = argv[i];
        int cantidad = atoi(argv[i+1]);
        // Buscar y despachar nodo con el código del producto
        despacharProducto(lista, despachados, codProducto, cantidad);
        // Si hay una cantidad restante, colocar como faltante
        if (cantidad > 0) {
            archivo << setw(MAX_PRODUCTO) << codProducto << setw(MAX_CANTIDAD)
                    << cantidad << endl;
        }
    }
}

void despacharProducto(void*& lista, void*& despachados, char* codProductoBuscado,
        int& cantidad) {
    void **nodoActual = (void**)lista, **nodoAnterior = NULL;
    while (nodoActual != NULL && cantidad > 0) {
        // Obtener datos del registro
        void** registro = (void**)(nodoActual[0]);
        char* codProductoLeido = (char*)(registro[0]);
        // Verificar si es el producto deseado
        int resultado = strcmp(codProductoLeido, codProductoBuscado);
        if (resultado > 0) {
            // Caso 1: Ya no hay más productos, salir
            break;
        } else if (resultado == 0) {
            // Caso 2: Es el producto buscado
            actualizarPalet(lista, despachados, nodoAnterior, nodoActual,
                    registro, cantidad);
        } else {
            // Caso 3: Seguir recorriendo hasta encontrar el producto deseado
            nodoAnterior = nodoActual;
        }
        // Avanzar al siguiente nodo
        nodoActual = (void**)(nodoActual[1]);
    }
}

void actualizarPalet(void* &lista, void* &despachados, void** &nodoAnterior,
        void** &nodoActual, void** registro, int &cantidad) {
    // Obtener datos del registro
    char* codProducto = (char*)(registro[0]);
    char* codPalet = (char*)(registro[1]);
    int* stock = (int*)(registro[2]);
    // Actualizar dependiendo de si hay suficiente stock en este palet o no
    if (*stock > cantidad) {
        // Disminuir stock
        *stock -= cantidad;
        // Agregar cantidad al despacho
        void* despacho = crearRegistro(codProducto, codPalet, cantidad);
        encola(despachados, despacho);
        // Indicar que se consumieron todos los productos
        cantidad = 0;
    } else {
        // Actualizar cantidad
        cantidad -= *stock;
        // Agregar cantidad al despacho
        encola(despachados, registro);
        // Quitar nodo de la lista
        if (nodoAnterior == NULL) {
            lista = nodoActual[1];
        } else {
            nodoAnterior[1] = nodoActual[1];
        }
    }
}

void imprimedespachados(void* despachados, void(*funcionImprimir)(ofstream&, void*)) {
    // Abrir archivo de salida
    ofstream archivo("files/Despachados.txt", ios::out);
    if (!archivo) {
        cerr << "No se pudo generar el archivo de despachos." << endl;
        exit(1);
    }
    // Imprimir todos los despachos
    while (despachados != NULL) {
        void* registro = desencola(despachados);
        funcionImprimir(archivo, registro);
    }
}
