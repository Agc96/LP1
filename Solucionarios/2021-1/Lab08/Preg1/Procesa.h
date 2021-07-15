/*
 * Archivo: Procesa.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:45 AM
 */

#ifndef PROCESA_H
#define PROCESA_H

#include <iostream>
#include "Registro.h"
using namespace std;

#define MAX_REGISTROS 1000

class Procesa {
public:
    Procesa(); // No es necesario usar un constructor copia
    virtual ~Procesa();
    // Métodos principales
    void lee();
    void imprime();
    void consolida();
private:
    Registro lregistro[MAX_REGISTROS];
    int cantidad;
    // Pregunta 1: Lectura de datos
    ifstream abrirArchivo(const char* nomArch);
    void guardarNombreConductor();
    void buscarDatosInfraccion(int codInfBuscado);
    void buscarDatosAdicionales(ifstream&, int, double&, int&, int&);
    // Pregunta 1: Impresión del reporte de prueba
    ofstream crearArchivo(const char* nomArch);
    void imprimirLinea(ofstream& arch, char c, int num);
};

#endif /* PROCESA_H */

