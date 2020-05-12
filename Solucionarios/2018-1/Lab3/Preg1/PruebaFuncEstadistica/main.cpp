/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 19 de septiembre de 2019, 04:21 PM
 */

#include <iostream>
#include <iomanip>
#include "funcEstadistica.h"
#define NUM_DATOS 100
#define NUM_LIMITES 5
using namespace std;

int main() {
    // Datos de prueba
    int datos[NUM_DATOS] = {
        30, 77, 35, 21, 70, 40, 29, 47, 4, 75,
        100, 2, 67, 5, 96, 60, 7, 71, 79, 1,
        7, 38, 90, 43, 28, 66, 25, 39, 2, 14,
        55, 60, 10, 29, 28, 20, 55, 41, 52, 34,
        43, 36, 39, 75, 91, 99, 39, 13, 64, 38,
        27, 81, 34, 1, 96, 87, 49, 65, 24, 96,
        93, 25, 100, 36, 3, 8, 11, 33, 21, 18,
        65, 3, 44, 48, 1, 46, 60, 100, 2, 98,
        83, 19, 35, 58, 100, 7, 97, 16, 98, 18,
        49, 88, 84, 33, 97, 15, 78, 67, 16, 20
    };
    int pesos[NUM_DATOS] = {
        10, 10, 9, 3, 10, 2, 1, 2, 8, 3,
        7, 1, 5, 5, 2, 8, 2, 6, 4, 3,
        4, 4, 3, 5, 9, 1, 10, 2, 9, 3,
        3, 2, 8, 1, 8, 2, 5, 5, 1, 9,
        1, 4, 5, 10, 3, 10, 10, 3, 8, 7,
        5, 8, 3, 3, 2, 5, 5, 10, 7, 6,
        5, 5, 5, 7, 4, 5, 4, 5, 7, 8,
        9, 10, 7, 5, 5, 2, 4, 8, 1, 6,
        7, 10, 10, 1, 7, 6, 3, 9, 1, 7,
        6, 9, 8, 4, 8, 9, 5, 2, 1, 4
    };
    int limites[NUM_LIMITES] = {10, 20, 40, 70, 90};
    int frecuencias[NUM_LIMITES + 1] = {0};
    // Pruebas de las funciones
    cout << left << fixed << setprecision(4);
    cout << "Media aritmetica: " << mediaAritmetica(datos, NUM_DATOS) << endl;
    cout << "Media ponderada: " << mediaPonderada(datos, pesos, NUM_DATOS) << endl;
    cout << "Mediana: " << mediana(datos, NUM_DATOS) << endl;
    cout << "Desviación estándar: " << desvEstandar(datos, NUM_DATOS) << endl;
    cout << "Frecuencias: " << endl;
    distFrecuencias(datos, NUM_DATOS, limites, NUM_LIMITES, frecuencias);
    for (int i = 0; i <= NUM_LIMITES; i++) {
        int limInferior = (i == 0) ? 0 : limites[i - 1];
        char simboloInferior = (i == 0) ? '[' : ']';
        int limSuperior = (i < NUM_LIMITES) ? limites[i] : NUM_DATOS;
        cout << simboloInferior << limInferior << ", " << limSuperior << "]: ";
        cout << frecuencias[i] << endl;
    }
    return 0;
}

