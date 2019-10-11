/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 11 de octubre de 2019, 10:37 AM
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
using namespace std;

void leerPalets(void*& palets) {
    ifstream archivo("files/Stock.txt", ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de stocks." << endl;
        exit(1);
    }
    void *buffer[MAX_BUFFER], *palet;
    int cantidad = 0;
    // Leer el archivo de entrada
    while (true) {
        palet = generarPalet(archivo);
        if (palet == NULL) break;
        buffer[cantidad++] = palet;
    }
    // Copiar los datos del búfer en un arreglo dinámico exacto
    palets = generarArregloExacto(buffer, cantidad);
}

void* generarPalet(ifstream& archivo) {
    char linea[MAX_LINEA], *codProducto, *codPalet;
    int *cantProductos;
    void** palet;
    // Leer el código del producto
    archivo.getline(linea, MAX_LINEA, ' ');
    if (archivo.eof()) return NULL;
    codProducto = new char[strlen(linea) + 1];
    strcpy(codProducto, linea);
    // Leer el código del palet
    archivo.getline(linea, MAX_LINEA, ' ');
    codPalet = new char[strlen(linea) + 1];
    strcpy(codPalet, linea);
    // Leer la cantidad de productos
    cantProductos = new int;
    archivo >> (*cantProductos) >> ws;
    // Guardar los datos del palet
    palet = new void*[3];
    palet[0] = codProducto;
    palet[1] = codPalet;
    palet[2] = cantProductos;
    return palet;
}

void* generarArregloExacto(void* buffer[], int cantidad) {
    void** puntero = new void*[cantidad + 1];
    for (int i = 0; i < cantidad; i++) {
        puntero[i] = buffer[i];
    }
    puntero[cantidad] = NULL;
    return puntero;
}

void imprimirPalets(void* palets) {
    ofstream archivo("files/Reporte.txt", ios::out);
    if (!archivo) {
        cerr << "No se pudo generar el reporte de palets." << endl;
        exit(1);
    }
    // Imprimir cabecera
    archivo << left << setw(MAX_CODIGO) << "Código del producto"
            << setw(MAX_CODIGO) << "Código del palet"
            << setw(MAX_NUM) << "Cantidad de productos" << endl;
    separacion(archivo);
    // Imprimir cada palet
    void*** arreglo = (void***)palets;
    for (int i = 0; arreglo[i] != NULL; i++) {
        imprimirPalet(archivo, arreglo[i]);
    }
    archivo << endl;
}

void imprimirPalet(ofstream& archivo, void** palet) {
    char* codProducto = (char*)palet[0];
    char* codPalet = (char*)palet[1];
    int* cantidad = (int*)palet[2];
    archivo << left << setw(MAX_CODIGO) << codProducto
            << setw(MAX_CODIGO) << codPalet
            << right << setw(MAX_NUM) << *cantidad << endl;
}

void separacion(ofstream& archivo, char car, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        archivo.put(car);
    }
    archivo << endl;
}

void leerProductos(void*& productos) {
    ifstream archivo("files/Productos.csv", ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de productos." << endl;
        exit(1);
    }
    void *buffer[MAX_BUFFER], *producto;
    int cantidad = 0;
    // Leer el archivo de entrada
    while (true) {
        producto = generarProducto(archivo);
        if (producto == NULL) break;
        buffer[cantidad++] = producto;
    }
    // Copiar los datos del búfer en un arreglo dinámico exacto
    productos = generarArregloExacto(buffer, cantidad);
}

void* generarProducto(ifstream& archivo) {
    char linea[MAX_LINEA], *codigo, *nombre;
    int *stock;
    void** producto;
    // Leer el código del producto
    archivo.getline(linea, MAX_LINEA, ',');
    if (archivo.eof()) return NULL;
    codigo = new char[strlen(linea) + 1];
    strcpy(codigo, linea);
    // Leer el nombre del producto
    archivo.getline(linea, MAX_LINEA);
    nombre = new char[strlen(linea) + 1];
    strcpy(nombre, linea);
    // Inicializar el stock en 0
    stock = new int;
    *stock = 0;
    // Guardar los datos del producto
    producto = new void*[3];
    producto[0] = codigo;
    producto[1] = nombre;
    producto[2] = stock;
    return producto;
}

void imprimirProductos(void* productos) {
    ofstream archivo("files/Reporte.txt", ios::out | ios::app);
    if (!archivo) {
        cerr << "No se pudo generar el reporte de productos." << endl;
        exit(1);
    }
    // Imprimir cabecera
    archivo << left << setw(MAX_NOMBRE) << "Nombre del producto"
            << setw(MAX_CODIGO) << "Código del producto"
            << setw(MAX_NUM) << "Cantidad de productos" << endl;
    separacion(archivo);
    // Imprimir cada palet
    void*** arreglo = (void***)productos;
    for (int i = 0; arreglo[i] != NULL; i++) {
        imprimirProducto(archivo, arreglo[i]);
    }
    archivo << endl;
}

void imprimirProducto(ofstream& archivo, void** producto) {
    char* codigo = (char*)producto[0];
    char* nombre = (char*)producto[1];
    int* stock = (int*)producto[2];
    archivo << left << setw(MAX_NOMBRE) << nombre
            << setw(MAX_CODIGO) << codigo
            << right << setw(MAX_NUM) << *stock << endl;
}

void ordenarProductos(void* productos) {
    void*** arreglo = (void***)productos;
    int cantidad;
    // Obtener la cantidad de productos
    for (cantidad = 0; arreglo[cantidad] != NULL; cantidad++);
    // Iniciar QuickSort
    ordenarProductos(arreglo, 0, cantidad - 1);
}

void ordenarProductos(void*** productos, int izq, int der) {
    if (izq >= der) return;
    // Elegimos el pivote (elemento que se colocará a la derecha)
    void** pivote = productos[der];
    char *nombrePivote = (char*) pivote[1], *nombre;
    // Empezamos en el índice del elemento más pequeño
    int limite = izq;
    for (int i = izq; i < der; i++) {
        // Verificamos si el elemento actual es menor que el pivote
        nombre = (char*)productos[i][1];
        if (strcmp(nombre, nombrePivote) < 0) {
            cambiarProductos(productos, limite++, i);
        }
    }
    cambiarProductos(productos, limite, der);
    ordenarProductos(productos, izq, limite - 1);
    ordenarProductos(productos, limite + 1, der);
}

void cambiarProductos(void*** productos, int izq, int der) {
    void** aux = productos[izq];
    productos[izq] = productos[der];
    productos[der] = aux;
}

void cargaStock(void* palets, void* productos) {
    void ***arrPalets = (void***)palets, ***arrProductos = (void***)productos;
    char *producto;
    int *stock;
    // Actualizar stocks
    for (int i = 0; arrProductos[i] != NULL; i++) {
        producto = (char*)arrProductos[i][0];
        stock = (int*)arrProductos[i][2];
        *stock = calcularStock(arrPalets, producto);
    }
    // Imprimir reporte de productos;
    imprimirProductos(productos);
}

int calcularStock(void*** palets, char* codProdBuscado) {
    int stock = 0, *cantLeida;
    char *codProdLeido;
    for (int i = 0; palets[i] != NULL; i++) {
        codProdLeido = (char*)palets[i][0];
        if (strcmp(codProdBuscado, codProdLeido) == 0) {
            cantLeida = (int*)palets[i][2];
            stock += *cantLeida;
        }
    }
    return stock;
}
