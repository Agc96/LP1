/*
 * File: utils.cpp
 * Author: Anthony Gutiérrez (20130095)
 */

#include <iostream>
#include <iomanip>
#include "utils.h"

using namespace std;

int main(int argc, char** argv) {
    // Declaración de variables
    int codigo, anexo, dia, mes, anho, longitudEmpleado;
    double tiempo;
    char c;
    bool fechaNuevaLinea, tiempoNuevaLinea;
    // Escribir cabecera
    cabecera();
    // Ir línea por línea
    while (true) {
        c = cin.peek();
        if (cin.eof()) break;
        // Separar un empleado del siguiente
        separacion('-', MAX_LINEA);
        // Leer y escribir el código (número)
        cin >> codigo;
        cout << setw(8) << setfill('0') << codigo;
        espacio(2);
        // Buscar el anexo (número) o leer una palabra del empleado
        longitudEmpleado = 0;
        while (!(cin >> anexo)) {
            cin.clear();
            // Colocar un espacio para separar las palabras
            if (longitudEmpleado > 0) {
                cout.put(' ');
                longitudEmpleado++;
            }
            // Escribir el nombre del empleado hasta encontrar un espacio
            while ((c = cin.get()) != ' ') {
                cout.put(c);
                longitudEmpleado++;
            }
        }
        espacio(MAX_EMPLEADO - longitudEmpleado + 2);
        // Escribir el anexo
        cout << setw(5) << setfill(' ') << anexo;
        espacio(2);
        // Buscar una fecha
        fechaNuevaLinea = false;
        tiempoNuevaLinea = false;
        while (true) {
            // Ver si llegamos al cambio de línea o de palabra
            c = cin.get();
            if (c == '\r') continue;
            if (c == '\n') break;
            if (c == ' ') continue;
            cin.unget();
            // Intentar leer un tiempo
            cin >> tiempo;
            if (cin.peek() == '/') {
                // En realidad es una fecha, terminar de leerla
                dia = tiempo;
                cin >> c >> mes >> c >> anho;
                // Colocar espacios antes de la fecha si es necesario
                if (fechaNuevaLinea) {
                    espacio(SEP_FECHA);
                } else {
                    fechaNuevaLinea = true;
                }
                // Imprimir la fecha
                cout << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/' << anho;
                espacio(2);
                tiempoNuevaLinea = false;
            } else {
                if (tiempoNuevaLinea) {
                    espacio(SEP_TIEMPO);
                } else {
                    tiempoNuevaLinea = true;
                }
                // Imprimir el tiempo
                cout << setfill(' ') << setw(7) << setprecision(2) << fixed << tiempo;
                cout << endl;
            }
        }
    }
    return 0;
}
