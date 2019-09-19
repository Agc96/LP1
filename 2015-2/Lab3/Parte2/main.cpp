/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Agutierrez
 *
 * Created on 18 de septiembre de 2019, 06:34 PM
 */

#include <iostream>
#include <iomanip>
#include "calculaTIR.h"
#include "utilidades.h"

#define MAX_FLUJOS 20
#define MAX_PROYECTO 40
#define MAX_CABECERA 20
#define MAX_TIR 10

using namespace std;

int main() {
    // Declaración de variables
    int numFlujos, longProyecto;
    double tasaCorte, inicial, flujos[MAX_FLUJOS], tasa;
    char c;
    // Configuración de la salida
    cout << left << fixed << setprecision(2);
    // Leer y escribir la tasa de corte
    cin >> tasaCorte;
    while (cin.get() != '\n');
    cout << "Tasa de corte: " << tasaCorte << '%' << endl;
    // Escribir cabecera
    cout << setw(MAX_PROYECTO) << "PROYECTO" << setw(MAX_CABECERA) << "TIR";
    cout << setw(MAX_CABECERA) << "COMENTARIOS" << endl;
    // Leer línea por línea
    while (true) {
        c = cin.get();
        if (cin.eof()) break;
        // Leer y escribir nombre del proyecto
        cout.put(c);
        longProyecto = 0;
        while (!(cin >> inicial)) {
            cin.clear();
            while ((c = cin.get()) != ' ') {
                cout.put(c);
                longProyecto++;
            }
            cout.put(' ');
            longProyecto++;
        }
        espacios(MAX_PROYECTO - longProyecto - 1);
        // Leer flujos de caja
        numFlujos = 0;
        while (cin >> flujos[numFlujos]) {
            numFlujos++;
        }
        cin.clear();
        // Calcular y escribir el TIR
        tasa = tir(inicial, numFlujos, flujos);
        cout << right << setw(MAX_TIR) << tasa << left << setw(MAX_TIR) << '%';
        // Imprimir comentarios
        if (tasa >= tasaCorte) {
            cout << "APROBADO" << endl;
        } else {
            cout << "RECHAZADO" << endl;
        }
    }
    return 0;
}
