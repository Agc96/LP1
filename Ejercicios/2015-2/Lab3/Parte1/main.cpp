/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Created on 18 de septiembre de 2019, 05:34 PM
 */

#include <iostream>
#include <iomanip>
#include "calculaTIR.h"
using namespace std;

int main() {
    double inicial = 23559.85;
    double coeficientes[] = {2500.35, 1250.4, 4568.95, 10723.00, 8056.21};
    cout << "Prueba TIR" << endl;
    double tasa = tir(inicial, 5, coeficientes);
    cout << fixed << setprecision(4);
    cout << "El valor del TIR es: " << (tasa*100) << "%" << endl;
    return 0;
}

