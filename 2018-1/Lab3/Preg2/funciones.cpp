/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 19 de septiembre de 2019, 08:56 PM
 */

#include <iostream>
#include <iomanip>
#include <cctype>
#include "constantes.h"
#include "utilidades.h"
using namespace std;

void escribirNombre(char parada, int maxCaracteres) {
    int numCaracteres = 0;
    char c;
    while ((c = cin.get()) != parada) {
        cout.put(toupper(c));
        numCaracteres++;
    }
    espacios(maxCaracteres - numCaracteres);
}

int leerRegistros(double* &intensidades, int* &duraciones, int* &fechas, int* &horas) {
    int tempDuraciones[MAX_REGISTROS], tempFechas[MAX_REGISTROS],
            tempHoras[MAX_REGISTROS], numRegistros = 0, dd, mm, aa, hh, ss;
    double tempIntensidades[MAX_REGISTROS];
    char c;
    // Leer cada registro
    while (cin >> tempIntensidades[numRegistros]) {
        // Leer y guardar duración
        cin >> tempDuraciones[numRegistros];
        // Leer y guardar fecha
        cin >> dd >> c >> mm >> c >> aa;
        tempFechas[numRegistros] = 10000*aa + 100*mm + dd;
        // Leer y guardar hora
        cin >> hh >> c >> mm >> c >> ss;
        tempHoras[numRegistros++] = 3600*hh + 60*mm + ss;
    }
    // Asignar dinámicamente los registros
    intensidades = new double[numRegistros];
    duraciones = new int[numRegistros];
    fechas = new int[numRegistros];
    horas = new int[numRegistros];
    for (int i = 0; i < numRegistros; i++) {
        intensidades[i] = tempIntensidades[i];
        duraciones[i] = tempDuraciones[i];
        fechas[i] = tempFechas[i];
        horas[i] = tempHoras[i];
    }
    return numRegistros;
}

void escribirRegistro(double* intensidades, int* duraciones, int* fechas,
        int* horas, int indice) {
    // Escribir intensidad
    cout << right << setw(MAX_DECIMAL) << intensidades[indice];
    espacios(MAX_INTENSIDAD - MAX_DECIMAL);
    // Escribir duración
    cout << setw(MAX_ENTERO) << duraciones[indice];
    espacios(MAX_DURACION - MAX_ENTERO);
    // Calcular y escribir fecha
    cout << right << setfill('0');
    cout << setw(2) << (fechas[indice] % 100) << '/';
    cout << setw(2) << ((fechas[indice] % 10000) / 100) << '/';
    cout << setw(4) << (fechas[indice] / 10000);
    espacios(MAX_FECHA - 10);
    // Calcular y escribir hora
    cout << setw(2) << (horas[indice] / 3600) << ':';
    cout << setw(2) << ((horas[indice] / 60) % 60) << ':';
    cout << setw(2) << (horas[indice] % 60) << setfill(' ');
    espacios(MAX_HORA - 8);
}

bool fechaEsMayor(int fecha1, int hora1, int fecha2, int hora2) {
    return (fecha1 > fecha2) || ((fecha1 == fecha2) && (hora1 > hora2));
}
