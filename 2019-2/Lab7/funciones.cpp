/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:33 AM
 */

#include "funciones.h"

void* leerRegistro(ifstream& archivo) {
    char linea[MAX_LINEA];
    // Leer código del producto en palet 
    archivo.getline(linea, MAX_LINEA, ',');
    char* codProducto = new char[strlen(linea) + 1];
    strcpy(codProducto, linea);
    // Leer código del palet
    archivo.getline(linea, MAX_LINEA, ',');
    char* codPalet = new char[strlen(linea) + 1];
    strcpy(codPalet, linea);
    // Leer cantidad de productos
    int cantidad;
    archivo >> cantidad >> ws;
    // Generar nuevo registro
    return crearRegistro(codProducto, codPalet, cantidad);
}

void* crearRegistro(char* codProducto, char* codPalet, int cantidad) {
    // Crear puntero con la cantidad
    int* puntero = new int;
    *puntero = cantidad;
    // Crear el registro
    void** registro = new void*[3];
    registro[0] = codProducto;
    registro[1] = codPalet;
    registro[2] = puntero;
    return registro;
}

int comparar(const void* primero, const void* segundo) {
    // Declaración de variables
    void** paletPrimero = (void**)primero;
    void** paletSegundo = (void**)segundo;
    char* codProdPrimero = (char*)(paletPrimero[0]);
    char* codProdSegundo = (char*)(paletSegundo[0]);
    // Comparar códigos de productos
    return strcmp(codProdPrimero, codProdSegundo);
}

void imprimeRegistro(ofstream& archivo, void* registro) {
    // Declaración de variables
    void** palet = (void**)registro;
    char* codProducto = (char*)(palet[0]);
    char* codPalet = (char*)(palet[1]);
    int* cantidad = (int*)(palet[2]);
    // Imprimir datos de forma tabulada
    archivo << setw(MAX_PRODUCTO) << codProducto << setw(MAX_PALET) << codPalet
            << setw(MAX_CANTIDAD) << *cantidad << endl;
}
