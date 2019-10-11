/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 30 de septiembre de 2019, 05:30 PM
 */

#include "funciones.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int leerArchivos(Cadena codigos[], Cadena cursos[], Cadena especialidades[],
        double creditos[]) {
    // Abrir el archivo
    ifstream archivo("files/Cursos.csv", ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de cursos." << endl;
        exit(1);
    }
    // Leer los datos del archivo
    int numRegistros = 0;
    char c;
    while (true) {
        // Leer y recortar código del curso
        leer(archivo, codigos[numRegistros], ',');
        if (archivo.eof()) break;
        recortar(codigos[numRegistros]);
        // Leer y recortar nombre del curso
        leer(archivo, cursos[numRegistros], ',');
        recortar(cursos[numRegistros]);
        // Leer número de créditos
        archivo >> creditos[numRegistros] >> ws >> c;
        // Leer y recortar nombres de cursos
        leer(archivo, especialidades[numRegistros]);
        recortar(especialidades[numRegistros++]);
    }
    return numRegistros;
}

void ordenarDatos(Cadena codigos[], Cadena cursos[], Cadena especialidades[],
        double creditos[], int limIzq, int limDer) {
    if (limIzq >= limDer) return;
    // Elegir el pivote del conjunto de elementos a ordenar
    cambiarDatos(codigos, cursos, especialidades, creditos, limIzq, (limIzq + limDer) / 2);
    int pivote = limIzq;
    // Resituar los demás elementos de la lista a cada lado del pivote
    // A un lado quedarán todos los menores que él, y al otro los mayores
    for (int i = limIzq + 1; i <= limDer; i++) {
        if (especialidades[i] < especialidades[limIzq]) {
            cambiarDatos(codigos, cursos, especialidades, creditos, ++pivote, i);
        }
    }
    cambiarDatos(codigos, cursos, especialidades, creditos, limIzq, pivote);
    // Llamar de forma recursiva para cada sublista
    ordenarDatos(codigos, cursos, especialidades, creditos, limIzq, pivote - 1);
    ordenarDatos(codigos, cursos, especialidades, creditos, pivote + 1, limDer);
}

void cambiarDatos(Cadena codigos[], Cadena cursos[], Cadena especialidades[],
        double creditos[], int indiceIzq, int indiceDer) {
    // Intercambiar cadenas
    intercambiar(codigos[indiceIzq], codigos[indiceDer]);
    intercambiar(cursos[indiceIzq], cursos[indiceDer]);
    intercambiar(especialidades[indiceIzq], especialidades[indiceDer]);
    // Intercambiar número de créditos (double)
    double temp = creditos[indiceIzq];
    creditos[indiceIzq] = creditos[indiceDer];
    creditos[indiceDer] = temp;
}

void imprimirReporte(Cadena codigos[], Cadena cursos[], Cadena especialidades[],
        double creditos[], int numRegistros) {
    // Abrir el archivo
    ofstream reporte("files/Reporte.txt", ios::out);
    if (!reporte) {
        cerr << "No se pudo generar el archivo del reporte." << endl;
        exit(1);
    }
    // Declaración de variables
    Cadena codigoAnterior;
    double sumaCreditos = 0;
    // Imprimir cabecera
    reporte << left << fixed << setprecision(2)
            << setw(MAX_NUM) << "No"
            << setw(MAX_ESPECIALIDAD) << "ESPECIALIDAD"
            << setw(MAX_CODIGO) << "CODIGO"
            << setw(MAX_CURSO) << "CURSO"
            << setw(MAX_CREDITOS) << "CREDITOS" << endl;
    repetir(reporte, '=', MAX_LINEA, true);
    // Escribir los datos de cada registro en el reporte
    for (int i = 0; i < numRegistros; i++) {
        reporte << right << setw(MAX_NUM - 3) << (i+1) << ")  ";
        reporte << especialidades[i];
        repetir(reporte, ' ', MAX_ESPECIALIDAD - longitud(especialidades[i]));
        reporte << codigos[i] << ' ';
        repetir(reporte, ' ', MAX_CODIGO - longitud(codigos[i]));
        reporte << cursos[i] << ' ';
        repetir(reporte, ' ', MAX_CURSO - longitud(cursos[i]));
        reporte << creditos[i] << endl;
        if (codigos[i] > codigoAnterior) {
            imprimirResumen(reporte, codigoAnterior, codigos[i], sumaCreditos);
        }
        sumaCreditos += creditos[i];
    }
    imprimirResumen(reporte, codigoAnterior, codigos[numRegistros - 1], sumaCreditos);
}

void imprimirResumen(ofstream& reporte, Cadena& codigoAnterior, Cadena& codigo,
        double& sumaCreditos) {
    if (longitud(codigoAnterior) > 0) {
        repetir(reporte, '-', MAX_LINEA, true);
        reporte << setw(MAX_NUM+MAX_ESPECIALIDAD+MAX_CODIGO+MAX_CURSO)
                << "Total de créditos: " << sumaCreditos << endl;
        repetir(reporte, '=', MAX_LINEA, true);
    }
    (codigoAnterior)&(codigo);
    sumaCreditos = 0;
}

void repetir(ofstream& reporte, char c, int cantidad, bool cambioLinea) {
    for (int i = 0; i < cantidad; i++) {
        reporte.put(c);
    }
    if (cambioLinea) {
        reporte << endl;
    }
}
