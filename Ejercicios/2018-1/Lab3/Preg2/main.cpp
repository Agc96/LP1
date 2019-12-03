/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 19 de septiembre de 2019, 05:44 PM
 */

#include <iostream>
#include <iomanip>
#include <climits>
#include "constantes.h"
#include "funciones.h"
#include "utilidades.h"
#include "funcEstadistica.h"
using namespace std;

int main() {
    // Declaración de variables
    int numCiudades = 0, numRegistros, *fechas, *horas, *duraciones, maxFecha,
            maxHora, maxFechaIndice, minFecha, minHora, minFechaIndice,
            minDuracion, maxDuracion;
    int limitesIntensidades[MAX_LIMITE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int limitesDuraciones[MAX_LIMITE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    double *intensidades, minIntensidad, maxIntensidad;
    char c;
    // Escribir título del reporte
    cout << left << fixed << setprecision(PRECISION);
    cout << "REPORTE DE LOS SISMOS A TRAVÉS DEL TIEMPO" << endl;
    // Leer cada línea del archivo
    while (true) {
        numCiudades++;
        // Escribir cabecera
        separacion('=', MAX_LINEA);
        cout << left << setw(MAX_NRO) << "No";
        cout << setw(MAX_PAIS) << "PAIS";
        cout << setw(MAX_CIUDAD) << "CIUDAD";
        cout << setw(MAX_INTENSIDAD) << "INTENSIDAD";
        cout << setw(MAX_DURACION) << "DURACION";
        cout << setw(MAX_FECHA) << "FECHA";
        cout << setw(MAX_HORA) << "HORA";
        cout << setw(MAX_OBSERVACION) << "OBSERVACION" << endl;
        separacion('=', MAX_LINEA);
        // Escribir número de la ciudad
        cout << right << setfill('0') << setw(2) << numCiudades;
        cout << left << setfill(' ');
        espacios(MAX_NRO - 2);
        // Leer y escribir país y ciudad
        escribirNombre(',', MAX_PAIS);
        escribirNombre(':', MAX_CIUDAD);
        // Leer y guardar registros
        numRegistros = leerRegistros(intensidades, duraciones, fechas, horas);
        // Calcular indicadores
        maxIntensidad = maxDuracion = maxFecha = maxHora = INT_MIN;
        minIntensidad = minDuracion = minFecha = minHora = INT_MAX;
        for (int i = 0; i < numRegistros; i++) {
            // Actualizar indicadores de intensidad
            if (intensidades[i] > maxIntensidad) maxIntensidad = intensidades[i];
            if (intensidades[i] < minIntensidad) minIntensidad = intensidades[i];
            // Actualizar indicadores de duración
            if (duraciones[i] > maxDuracion) maxDuracion = duraciones[i];
            if (duraciones[i] < minDuracion) minDuracion = duraciones[i];
            // Actualizar indicadores de fecha y hora
            if (fechaEsMayor(fechas[i], horas[i], maxFecha, maxHora)) {
                maxFecha = fechas[i];
                maxHora = horas[i];
                maxFechaIndice = i;
            }
            if (fechaEsMayor(minFecha, minHora, fechas[i], horas[i])) {
                minFecha = fechas[i];
                minHora = horas[i];
                minFechaIndice = i;
            }
        }
        // Escribir registros
        for (int i = 0; i < numRegistros; i++) {
            if (i != 0) espacios(MAX_NRO + MAX_PAIS + MAX_CIUDAD);
            // Escribir datos de un registro
            escribirRegistro(intensidades, duraciones, fechas, horas, i);
            // Colocar observaciones
            if (intensidades[i] == maxIntensidad) cout << "Máxima intensidad. ";
            if (intensidades[i] == minIntensidad) cout << "Mínima intensidad. ";
            if (duraciones[i] == maxDuracion) cout << "Máxima duración. ";
            if (duraciones[i] == minDuracion) cout << "Mínima duración. ";
            cout << endl;
        }
        // Escribir resumen
        separacion('-', MAX_LINEA);
        cout << left << "RESUMEN:" << endl;
        // Escribir sismo más antiguo
        cout << left << setw(MAX_NRO + MAX_PAIS + MAX_CIUDAD) << "SISMO MÁS ANTIGUO:";
        escribirRegistro(intensidades, duraciones, fechas, horas, minFechaIndice);
        cout << endl;
        // Escribir sismo más reciente
        cout << left << setw(MAX_NRO + MAX_PAIS + MAX_CIUDAD) << "SISMO MÁS RECIENTE:";
        escribirRegistro(intensidades, duraciones, fechas, horas, maxFechaIndice);
        cout << endl;
        // Escribir cabecera de información estadística
        separacion('*', MAX_LINEA);
        cout << "INFORMACIÓN ESTADÍSTICA" << endl;
        espacios(MAX_RESUMEN);
        cout << left << setw(MAX_RESUMEN) << "MEDIA ARITMÉTICA";
        cout << setw(MAX_RESUMEN) << "DESV. ESTÁNDAR";
        cout << setw(MAX_RESUMEN) << "MEDIANA" << endl;
        // Escribir información estadística de intensidades
        cout << left << setw(MAX_RESUMEN) << "INTENSIDADES:" << right;
        cout << setw(MAX_DECIMAL) << mediaAritmetica(intensidades, numRegistros);
        espacios(MAX_RESUMEN - MAX_DECIMAL);
        cout << setw(MAX_DECIMAL) << desvEstandar(intensidades, numRegistros);
        espacios(MAX_RESUMEN - MAX_DECIMAL);
        cout << setw(MAX_DECIMAL) << mediana(intensidades, numRegistros);
        espacios(MAX_RESUMEN - MAX_DECIMAL);
        cout << endl;
        // Escribir información estadística de duraciones
        cout << left << setw(MAX_RESUMEN) << "DURACIONES:" << right;
        cout << setw(MAX_DECIMAL) << mediaAritmetica(duraciones, numRegistros) << " seg.";
        espacios(MAX_RESUMEN - MAX_DECIMAL - 5);
        cout << setw(MAX_DECIMAL) << desvEstandar(duraciones, numRegistros);
        espacios(MAX_RESUMEN - MAX_DECIMAL);
        cout << setw(MAX_DECIMAL) << mediana(duraciones, numRegistros);
        espacios(MAX_RESUMEN - MAX_DECIMAL);
        cout << endl;
        // Distribución de frecuencias
        int* frecuenciasIntensidades = new int[MAX_LIMITE + 1];
        int* frecuenciasDuraciones = new int[MAX_LIMITE + 1];
        distFrecuencias(intensidades, numRegistros, limitesIntensidades,
                MAX_LIMITE, frecuenciasIntensidades);
        distFrecuencias(duraciones, numRegistros, limitesDuraciones,
                MAX_LIMITE, frecuenciasDuraciones);
        cout << "DISTRIBUCION DE FRECUENCIAS:" << endl;
        // TODO
        // Colocar cantidad de registros
        separacion('/', MAX_LINEA);
        cout << "CANTIDAD DE REGISTROS: " << numRegistros;
        separacion('/', MAX_LINEA);
        // Limpiar los arreglos dinámicos
        delete[] intensidades;
        delete[] duraciones;
        delete[] fechas;
        delete[] horas;
        delete[] frecuenciasIntensidades;
        delete[] frecuenciasDuraciones;
        // Verificar si terminó el programa
        if (cin.eof()) break;
        cin.clear();
    }
    return 0;
}
