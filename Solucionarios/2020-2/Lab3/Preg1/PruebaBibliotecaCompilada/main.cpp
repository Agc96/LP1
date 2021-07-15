/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de octubre de 2020, 08:45 AM
 */

#include "BibMedicos.h"

int main() {
    // Apertura de archivos
    ifstream archPrueba("Prueba.txt", ios::in);
    if (!archPrueba) {
        cerr << "No se pudo abrir el archivo Prueba.txt" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if (!archReporte) {
        cerr << "No se pudo generar el archivo Reporte.txt" << endl; 
        exit(1);
    }
    // Declaración de variables
    StMedico medico;
    StPaciente paciente;
    int dia, mes, anho;
    char c;
    // Lectura
    archPrueba >> medico;
    for (int i = 0; i < 4; i++) {
        archPrueba >> dia >> c >> mes >> c >> anho >> paciente;
        paciente.fecha = 10000 * anho + 100 * mes + dia;
        // Agregación
        medico + paciente;
    }
    // Modificación de estado
    medico + 20200212;
    // Cancelación de citas
    medico - 20200120;
    // Descarte
    medico / 20200115;
    // Cálculo de ingresos e impresión
    archReporte << medico;
    return 0;
}
