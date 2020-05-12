/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 4 de octubre de 2019, 11:11 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

void leerPalets(char***& almacenes) {
    // Apertura de archivos
    ifstream stock("Stock.txt", ios::in);
    if (!stock) {
        cerr << "No se pudo abrir el archivo de stock." << endl;
        exit(1);
    }
    // Declaración de variables
    int codigo, codigoAnterior = -1, contAlmacenes = 0, contProductos = 0;
    char **buffer[MAX_ALMACEN] = {NULL}, *producto;
    // Lectura del archivo de stocks
    while (stock >> codigo >> ws) {
        // Ver si los códigos han cambiado
        if (codigo != codigoAnterior) {
            if (codigoAnterior != -1) {
                incrementarAlmacen(buffer, NULL, contAlmacenes, contProductos);
                contAlmacenes++;
            }
            codigoAnterior = codigo;
            contProductos = 0;
        }
        // Leer código del producto
        producto = leerCodigoProducto(stock, ' ');
        incrementarAlmacen(buffer, producto, contAlmacenes, contProductos);
        // Ignorar código del pallet
        while (stock.get() != '\n');
    }
    incrementarAlmacen(buffer, NULL, contAlmacenes++, contProductos);
    // Colocar el búfer en el arreglo de almacenes
    almacenes = new char**[contAlmacenes + 1];
    for (int i = 0; i < contAlmacenes; i++) {
        almacenes[i] = buffer[i];
    }
    almacenes[contAlmacenes] = NULL;
}

char* leerCodigoProducto(istream& in, char parada) {
    char* producto = new char[TAM_CODIGO];
    in.getline(producto, TAM_CODIGO, parada);
    producto[TAM_CODIGO - 1] = '\0';
    return producto;
}

void incrementarAlmacen(char*** buffer, char* producto, int contAlmacenes,
        int& contProductos) {
    // Crear un nuevo almacén (arreglo de productos) y copiar los datos
    char** nuevoAlmacen = new char*[contProductos + 1];
    if (buffer[contAlmacenes] != NULL) {
        // Copiar los datos del arreglo anterior
        for (int i = 0; i < contProductos; i++) {
            nuevoAlmacen[i] = buffer[contAlmacenes][i];
        }
        delete[] buffer[contAlmacenes];
    }
    // Actualizar el nuevo arreglo
    nuevoAlmacen[contProductos++] = producto;
    buffer[contAlmacenes] = nuevoAlmacen;
}

void imprimirPalets(char*** almacenes) {
    // Apertura de archivos
    ofstream reporte("Reporte.txt", ios::out);
    if (!reporte) {
        cerr << "No se pudo generar el reporte para los pallets." << endl;
        exit(1);
    }
    // Imprimir cabecera
    reporte << "REPORTE DE ALMACENES" << endl;
    separacion(reporte);
    // Imprimir almacenes
    for (int i = 0; almacenes[i] != NULL; i++) {
        reporte << "ALMACÉN " << (i + 1) << endl;
        reporte << setw(MAX_NUMERO) << "No"
                << setw(MAX_CODIGO) << "Producto" << endl;
        // Imprimir productos del almacén
        char** productos = almacenes[i];
        for (int j = 0; productos[j] != NULL; j++) {
            reporte << setw(MAX_NUMERO) << (j + 1)
                    << setw(MAX_CODIGO) << productos[j] << endl;
        }
    }
    reporte << endl << endl;
}

void separacion(ostream& out, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        out.put(c);
    }
    out << endl;
}

void leerProductos(char**& codigoProd, char**& nombreProd) {
    // Apertura de archivos
    ifstream productos("Productos.csv", ios::in);
    if (!productos) {
        cerr << "No se pudo abrir el archivo de productos." << endl;
        exit(1);
    }
    // Declaración de variables
    char *bufferCodigo[MAX_PRODUCTOS], *bufferNombre[MAX_PRODUCTOS];
    int numProductos = 0;
    // Lectura del archivo de productos
    while (true) {
        // Leer el código del producto
        bufferCodigo[numProductos] = leerCodigoProducto(productos, ',');
        if (productos.eof()) break;
        // Leer el nombre del producto
        bufferNombre[numProductos++] = leerNombreProducto(productos);
    }
    // Copiar buffers en arreglos dinámicos
    codigoProd = new char*[numProductos + 1];
    nombreProd = new char*[numProductos + 1];
    for (int i = 0; i < numProductos; i++) {
        codigoProd[i] = bufferCodigo[i];
        nombreProd[i] = bufferNombre[i];
    }
    codigoProd[numProductos] = nombreProd[numProductos] = NULL;
}

char* leerNombreProducto(istream& in) {
    char bufferNombre[MAX_NOMBRE];
    in.getline(bufferNombre, MAX_NOMBRE);
    // Convertir a arreglo dinámico
    int tamCadena = strlen(bufferNombre);
    char* nombre = new char[tamCadena + 1];
    for (int i = 0; i < tamCadena; i++) {
        nombre[i] = bufferNombre[i];
    }
    nombre[tamCadena] = '\0';
    return nombre;
}

void imprimirProductos(char** codigoProd, char** nombreProd) {
    // Apertura de archivos
    ofstream reporte("Reporte.txt", ios::out | ios::app);
    if (!reporte) {
        cerr << "No se pudo generar el reporte para los productos." << endl;
        exit(1);
    }
    // Imprimir cabecera
    reporte << left << "REPORTE DE PRODUCTOS" << endl;
    separacion(reporte);
    reporte << setw(MAX_CODIGO) << "Codigo" << "Nombre" << endl;
    separacion(reporte, '-');
    // Imprimir datos del producto
    for (int i = 0; codigoProd[i] != NULL && nombreProd[i] != NULL; i++) {
        reporte << setw(MAX_CODIGO) << codigoProd[i] << nombreProd[i] << endl;
    }
    reporte << endl << endl;
}

void ordenarProductos(char** codigoProd, char** nombreProd) {
    int numProductos = 0;
    for (numProductos = 0; codigoProd[numProductos] != NULL; numProductos++);
    // Ordenar los productos
    ordenarProductos(codigoProd, nombreProd, 0, numProductos - 1);
}

void ordenarProductos(char** codigoProd, char** nombreProd, int izq, int der) {
    if (izq >= der) return;
    cambiarProductos(codigoProd, nombreProd, izq, (izq+der)/2);
    int limite = izq;
    for (int i = izq + 1; i <= der; i++) {
        if (strcmp(nombreProd[i], nombreProd[izq]) < 0) {
            cambiarProductos(codigoProd, nombreProd, ++limite, i);
        }
    }
    cambiarProductos(codigoProd, nombreProd, izq, limite);
    ordenarProductos(codigoProd, nombreProd, izq, limite-1);
    ordenarProductos(codigoProd, nombreProd, limite+1, der);
}

void cambiarProductos(char** codigoProd, char** nombreProd, int i, int j){
    // Guardar datos del producto i
    char* codigoAux = codigoProd[i];
    char* nombreAux = nombreProd[i];
    // Colocar datos del producto j en el producto i
    codigoProd[i] = codigoProd[j];
    nombreProd[i] = nombreProd[j];
    // Colocar datos del producto i en el producto j
    codigoProd[j] = codigoAux;
    nombreProd[j] = nombreAux;
}

void cuentaProductos(char*** almacenes, char** codigoProd, char** nombreProd) {// Apertura de archivos
    ofstream reporte("Reporte.txt", ios::out | ios::app);
    if (!reporte) {
        cerr << "No se pudo generar el reporte para el conteo de productos." << endl;
        exit(1);
    }
    // Imprimir cabecera
    reporte << left << "REPORTE DE CONTEO DE PRODUCTOS" << endl;
    separacion(reporte);
    reporte << setw(MAX_NOMBRE) << "Nombre de Producto"
            << setw(MAX_CABECERA) << "Código de Producto"
            << setw(MAX_CABECERA) << "Cantidad de Palets" << endl;
    separacion(reporte, '-');
    // Imprimir datos de productos
    int numPalets;
    for (int i = 0; codigoProd[i] != NULL && nombreProd[i] != NULL; i++) {
        numPalets = obtenerNumeroPalets(almacenes, codigoProd[i]);
        reporte << setw(MAX_NOMBRE) << nombreProd[i]
                << setw(MAX_CABECERA) << codigoProd[i]
                << setw(MAX_CABECERA) << numPalets << endl;
    }
}

int obtenerNumeroPalets(char*** almacenes, char* codProducto) {
    int numPalets = 0;
    for (int i = 0; almacenes[i] != NULL; i++) {
        char** productos = almacenes[i];
        for (int j = 0; productos[j] != NULL; j++) {
            if (strcmp(codProducto, productos[j]) == 0) numPalets++;
        }
    }
    return numPalets;
}
