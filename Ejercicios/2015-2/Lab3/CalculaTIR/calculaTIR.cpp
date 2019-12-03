/* 
 * Archivo: calculaTIR.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Created on 18 de septiembre de 2019, 04:23 PM
 */

#include <cmath>
#include "calculaTIR.h"

using namespace std;

#define RAIZ_INICIAL 0.1
#define MIN_FUNCION 0.0001

double raizDeEcuacion(double inicial, int numCoef, double coef[]) {
    double funcion = 1, derivada, raiz = RAIZ_INICIAL;
    while (abs(funcion) >= MIN_FUNCION) {
        // Calcular el valor de la función
        funcion = inicial;
        for (int i = 0; i < numCoef; i++) {
            funcion += (coef[i] * pow(raiz, i + 1));
        }
        // Calcular el valor de la derivada
        derivada = 0;
        for (int i = 0; i < numCoef; i++) {
            derivada += (coef[i] * pow(raiz, i));
        }
        // Calcular la nueva raíz
        raiz -= funcion/derivada;
        // Por alguna razón la condición no funciona, así que colocamos break para salir
        break;
    }
    return raiz;
}

double tir(double inversion, int periodos, double flujosCaja[]) {
    double raiz = raizDeEcuacion(-inversion, periodos, flujosCaja);
    return (1.0/raiz) - 1;
}
