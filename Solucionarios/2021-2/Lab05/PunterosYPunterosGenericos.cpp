/*
 * File:   PunterosYPunterosGenericos.c
 * Author: Anthony Gutiérrez
 *
 * Created on 15 de octubre de 2021, 12:35 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "PunterosYPunterosGenericos.h"
#include "FuncionesFecha.h"
using namespace std;

#define MAX_LIBROS 35
#define MAX_COD_LIBRO 8
#define MAX_NOM_LIBRO 32
#define MAX_NOM_USUARIO 35
#define INCREMENTO 5
#define MAX_DEUDAS 150
#define MAX_LINEA 140
#define NO_ENCONTRADO -1

enum Libro{COD_LIBRO, NOM_LIBRO, STOCK, PRECIO};
enum Deuda{CARNE, TIPO, LIBRO, FECHA};

void cargaDeLibros(void *&libros) {
    ifstream arch("Libros.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Libros.csv" << endl;
        exit(1);
    }
    void *buffLibros[MAX_LIBROS], **auxLibros;
    char codLibro[MAX_COD_LIBRO], nomLibro[40], c;
    int edicion, stock, cantLibros = 0;
    double precio;
    while (1) {
        arch.getline(codLibro, MAX_COD_LIBRO, ',');
        if (arch.eof()) break;
        arch.getline(nomLibro, MAX_NOM_LIBRO, ',');
        while (arch.get() != ',');
        arch >> edicion >> c >> stock >> c >> precio >> ws;
        auxLibros = new void*[4];
        auxLibros[COD_LIBRO] = crearCadenaExacta(codLibro);
        auxLibros[NOM_LIBRO] = crearCadenaExacta(nomLibro);
        auxLibros[STOCK] = crearIntExacto(stock);
        auxLibros[PRECIO] = crearDoubleExacto(precio);
        buffLibros[cantLibros++] = auxLibros;
    }
    libros = crearArrDinamicoExacto(buffLibros, cantLibros);
}

char *crearCadenaExacta(const char *buff) {
    char *cad = new char[strlen(buff)+1];
    strcpy(cad, buff);
    return cad;
}

int *crearIntExacto(int valor) {
    int *ptr = new int;
    *ptr = valor;
    return ptr;
}

double *crearDoubleExacto(double valor) {
    double *ptr = new double;
    *ptr = valor;
    return ptr;
}

void *crearArrDinamicoExacto(void **buff, int cant) {
    void **arr = new void*[cant+1];
    for (int i = 0; i < cant; i++) {
        arr[i] = buff[i];
    }
    arr[cant] = nullptr;
    return arr;
}

void reporteDeLibros(void *libros) {
    ofstream arch("ReporteLibros.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo ReporteLibros.txt" << endl;
        exit(1);
    }
    void **ptrLibros = (void **)libros, **libro;
    char *codLibro, *nomLibro;
    int *stock;
    double *precio;
    // Imprimir cabecera
    arch << fixed << setprecision(2);
    arch << left << setw(10) << "CODIGO" << setw(MAX_NOM_LIBRO) << "NOMBRE"
            << setw(9) << "STOCK" << "PRECIO" << endl;
    // Imprimir listado de libros
    for (int i = 0; ptrLibros[i] != nullptr; i++) {
        libro = (void **)ptrLibros[i];
        codLibro = (char *)libro[COD_LIBRO];
        nomLibro = (char *)libro[NOM_LIBRO];
        stock = (int *)libro[STOCK];
        precio = (double *)libro[PRECIO];
        arch << left << setw(10) << codLibro << setw(MAX_NOM_LIBRO) << nomLibro;
        arch << right << setw(5) << *stock << setw(10) << *precio << endl;
    }
}

void cargaDeUsuarios(int *&carne, char *&tipo, char **&nombre) {
    ifstream arch("Usuarios.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo Usuarios.csv" << endl;
        exit(1);
    }
    int buffCarne, cantUsuarios = 0;
    char buffTipo, buffNombre[MAX_NOM_USUARIO], c;
    while (1) {
        arch >> buffCarne;
        if (arch.eof()) break;
        arch >> buffTipo >> c;
        arch.getline(buffNombre, MAX_NOM_USUARIO);
        if (cantUsuarios == 0 || (cantUsuarios+1) % INCREMENTO == 0) {
            incrementarUsuarios(carne, tipo, nombre, cantUsuarios);
        }
        carne[cantUsuarios] = buffCarne;
        tipo[cantUsuarios] = buffTipo;
        nombre[cantUsuarios] = crearCadenaExacta(buffNombre);
        cantUsuarios++;
    }
}

void incrementarUsuarios(int *&carne, char *&tipo, char **&nombre, int cantUsuarios) {
    int tamArreglo = (cantUsuarios > 0) ? cantUsuarios+INCREMENTO+1 : INCREMENTO;
    int *auxCarne = new int[tamArreglo];
    char *auxTipo = new char[tamArreglo];
    char **auxNombre = new char*[tamArreglo];
    for (int i = 0; i < cantUsuarios; i++) {
        auxCarne[i] = carne[i];
        auxTipo[i] = tipo[i];
        auxNombre[i] = nombre[i];
    }
    for (int i = cantUsuarios; i < tamArreglo; i++) {
        auxCarne[i] = 0;
        auxTipo[i] = 0;
        auxNombre[i] = nullptr;
    }
    if (cantUsuarios > 0) {
        delete carne;
        delete tipo;
        delete nombre;
    }
    carne = auxCarne;
    tipo = auxTipo;
    nombre = auxNombre;
}

void reporteDeUsuarios(int *carne, char *tipo, char **nombre) {
    ofstream arch("ReporteUsuarios.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo ReporteUsuarios.txt" << endl; 
        exit(1);
    }
    // Imprimir cabecera
    arch << left << setw(10) << "CARNE" << setw(8) << "TIPO" << "NOMBRE" << endl;
    // Imprimir listado de usuarios
    for (int i = 0; carne[i] != 0; i++) {
        arch << setw(10) << carne[i] << setw(8) << tipo[i] << nombre[i] << endl;
    }
}

/* Pregunta 3 */

void reporteUsuariosInhabilitados(void *libros, int *carne, char *tipo, char **nombre) {
    ofstream arch("ReporteUsuariosInhabilitados.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo ReporteUsuariosInhabilitados.txt" << endl;
        exit(1);
    }
    void *deudas;
    int dd, mm, aaaa, fecha, indice = 1;
    char c;
    // Solicitar fecha inicial
    cout << "Ingrese la fecha de hoy (dd/mm/aaaa): ";
    cin >> dd >> c >> mm >> c >> aaaa;
    fecha = 10000*aaaa + 100*mm + dd;
    // Cargar datos de las deudas
    cargaDeDeudas(deudas, fecha);
    reporteDeDeudas(deudas);
    // Imprimir cabecera del reporte
    arch << fixed << setprecision(2);
    imprimirLinea(arch, '=');
    arch << right << setw(88) << "USUARIOS DEUDORES" << endl;
    // Imprimir lista de usuarios
    for (int i = 0; carne[i] != 0; i++) {
        imprimirDeudasUsuarios(arch, libros, carne[i], tipo[i], nombre[i],
                indice, deudas, fecha);
    }
    imprimirLinea(arch, '=');
}

void cargaDeDeudas(void *&deudas, int fechaHoy) {
    ifstream arch("RegistroDePrestamos.csv", ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo RegistroDePrestamos.csv" << endl;
        exit(1);
    }
    void *buffDeudas[MAX_DEUDAS], **auxDeudas;
    int carne, dd, mm, aaaa, fechaRetiro, cantDeudas = 0, maxDias;
    char tipo, c, codLibro[MAX_COD_LIBRO];
    while (1) {
        arch >> carne;
        if (arch.eof()) break;
        arch >> tipo >> c;
        arch.getline(codLibro, MAX_COD_LIBRO, ',');
        arch >> dd >> c >> mm >> c >> aaaa;
        fechaRetiro = 10000*aaaa + 100*mm + dd;
        // Solo agregar el dato si la fecha de hoy es mayor a la fecha de retiro
        maxDias = obtenerMaxDiasPorTipo(tipo);
        if (numeroDeDias(fechaRetiro, fechaHoy) > maxDias) {
            auxDeudas = new void*[4];
            auxDeudas[CARNE] = crearIntExacto(carne);
            auxDeudas[TIPO] = crearCharExacto(tipo);
            auxDeudas[LIBRO] = crearCadenaExacta(codLibro);
            auxDeudas[FECHA] = crearIntExacto(fechaRetiro);
            buffDeudas[cantDeudas++] = auxDeudas;
        }
    }
    deudas = crearArrDinamicoExacto(buffDeudas, cantDeudas);
}

int obtenerMaxDiasPorTipo(char tipo) {
    switch (tipo) {
        case 'A':
            return 3;
        case 'D':
            return 15;
        case 'E':
            return 7;
        default:
            cerr << "No se encontró el tipo de usuario " << tipo << endl;
            exit(1);
    }
}

char *crearCharExacto(char valor) {
    char *ptr = new char;
    *ptr = valor;
    return ptr;
}

void reporteDeDeudas(void *deudas) {
    ofstream arch("JpReporteDeDeudasCompleto.txt", ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo ReporteDeudas.txt" << endl;
        exit(1);
    }
    void **auxDeudas = (void **)deudas, **deuda;
    int *carne, *fecha;
    char *libro, *tipo;
    // Imprimir cabecera de deudas
    arch << left << setw(12) << "CARNE" << setw(8) << "TIPO" <<
            setw(10) << "LIBRO" << "FECHA" << endl;
    // Imprimir listado de deudas
    for (int i = 0; auxDeudas[i] != nullptr; i++) {
        deuda = (void **)auxDeudas[i];
        carne = (int *)deuda[CARNE];
        tipo = (char *)deuda[TIPO];
        libro = (char *)deuda[LIBRO];
        fecha = (int *)deuda[FECHA];
        arch << setw(12) << *carne << setw(8) << *tipo << setw(10) << libro
                << *fecha << endl;
    }
}

void imprimirDeudasUsuarios(ofstream &arch, void *libros, int carne, char tipo,
        char *nombre, int &indice, void *deudas, int fechaHoy) {
    void **auxDeudas = (void **)deudas, **deuda, **auxLibros;
    int *carneDeuda, *fechaRetiro, posLibro, dias;
    char *tipoDeuda, *codLibro;
    double total = 0, mora;
    bool primeraVez = true;
    // Buscar los préstamos que coinciden con el usuario
    for (int i = 0; auxDeudas[i] != nullptr; i++) {
        deuda = (void **)auxDeudas[i];
        carneDeuda = (int *)deuda[CARNE];
        tipoDeuda = (char *)deuda[TIPO];
        if (carne == *carneDeuda && tipo == *tipoDeuda) {
            codLibro = (char *)deuda[LIBRO];
            fechaRetiro = (int *)deuda[FECHA];
            // Verificar si el libro ha sido vencido
            posLibro = buscarLibro(libros, codLibro);
            if (posLibro != NO_ENCONTRADO) {
                auxLibros = (void **)libros;
                dias = numeroDeDias(*fechaRetiro, fechaHoy);
                mora = obtenerMoraPorTipo(tipo);
                imprimirLibroEndeudado(arch, auxLibros[posLibro], carne, tipo,
                        nombre, indice, dias, mora, primeraVez, total);
            }
        }
    }
    // Imprimir resumen de préstamo de ser necesario
    if (total > 0) {
        imprimirLinea(arch, '-');
        arch << right << setw(122) << "Total" << setw(16) << total << endl;
    }
}

int buscarLibro(void *libros, char *codBuscado) {
    void **auxLibros = (void **)libros, **libro;
    char *codLeido;
    for (int i = 0; auxLibros[i] != nullptr; i++) {
        libro = (void **)auxLibros[i];
        codLeido = (char *)libro[COD_LIBRO];
        if (strcmp(codBuscado, codLeido) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void imprimirLibroEndeudado(ofstream &arch, void *libro, int carne, char tipo,
        char *nombre, int &indice, int dias, double mora, bool &primeraVez,
        double &total) {
    void **auxLibro = (void **)libro;
    char *codLibro, *nomLibro;
    int *stock;
    double *precio, monto;
    // Imprimir cabecera de ser necesario
    if (primeraVez) {
        imprimirCabeceraUsuario(arch, carne, tipo, nombre, indice);
        primeraVez = false;
        indice++;
    } else {
        arch << left << setw(MAX_NOM_USUARIO + 30) << ' ';
    }
    // Calcular monto que debe el usuario
    codLibro = (char *)auxLibro[COD_LIBRO];
    nomLibro = (char *)auxLibro[NOM_LIBRO];
    stock = (int *)auxLibro[STOCK];
    precio = (double *)auxLibro[PRECIO];
    monto = (1 + mora*dias) * (*precio);
    // Imprimir datos del libro
    arch << setw(15) << codLibro << setw(MAX_NOM_LIBRO) << nomLibro
            << right << setw(8) << dias << setw(18) << monto << endl;
    total += monto;
}

void imprimirCabeceraUsuario(ofstream &arch, int carne, char tipo, char *nombre,
        int indice) {
    imprimirLinea(arch, '-');
    arch << left << setw(5) << "No." << setw(10) << "CARNE"
            << setw(MAX_NOM_USUARIO) << "NOMBRE" << setw(15) << "Tipo"
            << setw(15) << "COD. DE LIB" << setw(MAX_NOM_LIBRO) << "Titulo"
            << setw(22) << "DIAS DE RETRASO" << setw(6) << "DEBE" << endl;
    imprimirLinea(arch, '-');
    // Imprimir datos del usuario
    arch << right << setw(2) << indice << ")  " << left << setw(10) << carne
            << setw(MAX_NOM_USUARIO) << nombre;
    switch (tipo) {
        case 'A':
            arch << setw(15) << "Administrador";
            break;
        case 'D':
            arch << setw(15) << "Docente";
            break;
        case 'E':
            arch << setw(15) << "Estudiante";
            break;
    }
}

double obtenerMoraPorTipo(char tipo) {
    switch (tipo) {
        case 'A':
            return 0.0075; // 0.75%
        case 'D':
            return 0.01; // 1%
        case 'E':
            return 0.005; // 0.5%
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < MAX_LINEA; i++) {
        arch.put(car);
    }
    arch << endl;
}
