/* 
 * Archivo: FuncionesLab1Preg2.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "FuncionesLab1Preg2.h"
#define MAX_NOMBRE 100

enum Cliente {CODIGO, NOMBRE, HORA, TIEMPO};

void *leerCliente(ifstream &arch) {
    int codigo, hh, mm, ss, hora;
    double tiempo;
    char c, nombre[MAX_NOMBRE];
    void **cliente;
    // Leer el código del cliente
    arch >> codigo >> c;
    if (arch.eof()) return nullptr;
    // Leer el nombre del cliente
    arch.getline(nombre, MAX_NOMBRE, ',');
    // Leer la hora y el tiempo
    arch >> hh >> c >> mm >> c >> ss >> c >> tiempo;
    hora = 3600*hh + 60*mm + ss;
    // Crear els registro del cliente
    cliente = new void*[4];
    cliente[CODIGO] = crearEntero(codigo);
    cliente[NOMBRE] = crearCadena(nombre);
    cliente[HORA] = crearEntero(hora);
    cliente[TIEMPO] = crearDecimal(tiempo);
    return cliente;
}

void imprimirCliente(ofstream &arch, void *dato) {
    // Obtener los datos del cliente
    void **cliente = (void**)dato;
    int *codigo = (int*)(cliente[CODIGO]);
    char *nombre = (char*)(cliente[NOMBRE]);
    int *hora = (int*)(cliente[HORA]);
    double *tiempo = (double*)(cliente[TIEMPO]);
    // Imprimir los datos del cliente
    arch << right << setw(8) << *codigo << "  ";
    arch << left << setw(40) << nombre << "  ";
    arch << right << setw(8) << *hora << "  ";
    arch << fixed << setprecision(2) << setw(8) << *tiempo << "  " << endl;
}

void atiendeCola(void *&cola) {
    // TODO
}

/* Funciones auxiliares */

int *crearEntero(int valor) {
    int *ptr = new int;
    *ptr = valor;
    return ptr;
}

double *crearDecimal(double valor) {
    double *ptr = new double;
    *ptr = valor;
    return ptr;
}

char *crearCadena(char *original) {
    char *nuevo = new char[strlen(original)+1];
    strcpy(nuevo, original);
    return nuevo;
}
