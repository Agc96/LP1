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
    int codigo, anexo, dia, mes, anho, longitudEmpleado, inicioDia, inicioMes,
        inicioAnho, finDia, finMes, finAnho, inicio, fin, fecha, cantDias,
        cantLlamadas, totalLlamadas = 0, mayorDia, mayorMes, mayorAnho,
        totalMayorCodigo, totalMayorDia, totalMayorMes, totalMayorAnho;
    double tiempo, subtotalTiempo, resumenTiempo, promedioTiempo, mayorTiempo,
        totalTiempo = 0, totalMayorTiempo = 0;
    char c;
    bool fechaNuevaLinea, tiempoNuevaLinea, fechaEnRango;
    // Inicializar cin y cout
    cout.precision(2);
    cout.setf(cout.fixed);
    // Leer cabecera
    cin >> inicioDia >> c >> inicioMes >> c >> inicioAnho;
    cin >> finDia >> c >> finMes >> c >> finAnho;
    inicio = 10000*inicioAnho + 100*inicioMes + inicioDia;
    fin = 10000*finAnho + 100*finMes + finDia;
    // Escribir cabecera
    cabecera(inicioDia, inicioMes, inicioAnho, finDia, finMes, finAnho);
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
        fechaEnRango = true;
        cantDias = 0;
        cantLlamadas = 0;
        subtotalTiempo = 0;
        resumenTiempo = 0;
        mayorTiempo = 0;
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
                // Colocar el subtotal del tiempo
                if (subtotalTiempo > 0) {
                    espacio(SEP_FECHA);
                    separacion('-', MAX_LINEA - SEP_FECHA);
                    espacio(SEP_FECHA);
                    cout << "Total:";
                    espacio(6);
                    cout << setfill(' ');
                    cout << setw(7) << subtotalTiempo;
                    cout << endl;
                    espacio(SEP_FECHA);
                    separacion('-', MAX_LINEA - SEP_FECHA);
                    if (subtotalTiempo > totalMayorTiempo) {
                        totalMayorTiempo = subtotalTiempo;
                        totalMayorDia = dia;
                        totalMayorMes = mes;
                        totalMayorAnho = anho;
                        totalMayorCodigo = codigo;
                    }
                    subtotalTiempo = 0;
                }
                // Ver si la fecha se debe tomar en cuenta
                fecha = 10000*anho + 100*mes + dia;
                fechaEnRango = (inicio <= fecha) && (fecha <= fin);
                if (!fechaEnRango) continue;
                cantDias++;
                // Colocar espacios antes de la fecha si es necesario
                if (fechaNuevaLinea) {
                    espacio(SEP_FECHA);
                } else {
                    fechaNuevaLinea = true;
                }
                // Imprimir la fecha
                cout << setfill('0') << setw(2) << dia << '/';
                cout << setw(2) << mes << '/' << anho;
                espacio(2);
                tiempoNuevaLinea = false;
            } else {
                if (!fechaEnRango) continue;
                if (tiempoNuevaLinea) {
                    espacio(SEP_TIEMPO);
                } else {
                    tiempoNuevaLinea = true;
                }
                // Imprimir el tiempo
                cout << setfill(' ') << setw(7) << tiempo << endl;
                // Actualizar contadores
                cantLlamadas++;
                totalLlamadas++;
                subtotalTiempo += tiempo;
                resumenTiempo += tiempo;
                totalTiempo += tiempo;
                if (tiempo > mayorTiempo) {
                    mayorTiempo = tiempo;
                    mayorDia = dia;
                    mayorMes = mes;
                    mayorAnho = anho;
                }
            }
        }
        // Colocar el subtotal del tiempo
        if (subtotalTiempo > 0) {
            espacio(SEP_FECHA);
            separacion('-', MAX_LINEA - SEP_FECHA);
            espacio(SEP_FECHA);
            cout << "Total:";
            espacio(6);
            cout << setfill(' ') << setw(7) << subtotalTiempo << endl;
            if (subtotalTiempo > totalMayorTiempo) {
                totalMayorTiempo = subtotalTiempo;
                totalMayorDia = dia;
                totalMayorMes = mes;
                totalMayorAnho = anho;
                totalMayorCodigo = codigo;
            }
            subtotalTiempo = 0;
        }
        // Cambiar de línea si no hay fechas
        if (cantDias == 0) {
            cout << endl;
        }
        // Imprimir resumen
        separacion('*', MAX_LINEA);
        cout << "Resumen:" << endl;
        // Tiempo total de llamadas
        cout << "- Tiempo total de llamadas: ";
        cout << setw(10) << resumenTiempo << " segundos";
        imprimirHora(resumenTiempo, true);
        // Días contabilizados
        cout << "- Días contabilizados: " << cantDias << endl;
        // Promedio
        cout << "- Promedio: ";
        promedioTiempo = (cantLlamadas > 0) ? resumenTiempo / cantLlamadas : 0;
        cout << promedioTiempo;
        imprimirHora(promedioTiempo, true);
        // Día que más llamó
        cout << "- Día que más llamó: ";
        if (cantDias > 0) {
            imprimirFecha(mayorDia, mayorMes, mayorAnho, false);
        } else {
            imprimirFecha(0, 0, 0, false);
        }
        espacio(3);
        cout << "Total del día: " << mayorTiempo;
        imprimirHora(mayorTiempo, true);
    }
    separacion('=', MAX_LINEA);
    cout << "Resumen total:" << endl;
    cout << "- Tiempo total general de llamadas telefónicas: " << totalTiempo;
    imprimirHora(totalTiempo, true);
    cout << "- Cantidad total de llamadas telefónicas: " << totalLlamadas << endl;
    cout << "- Código del empleado que más llamó en un día: ";
    cout << setfill('0') << setw(8) << totalMayorCodigo << " con ";
    cout << totalMayorTiempo;
    imprimirHora(totalMayorTiempo, false);
    cout << " el ";
    imprimirFecha(totalMayorDia, totalMayorMes, totalMayorAnho, true);
    return 0;
}
