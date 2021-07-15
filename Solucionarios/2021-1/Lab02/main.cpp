/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 23 de abril de 2021, 07:48 AM
 */

#include "funciones.h"

int main() {
    /* Pregunta 1 */
    transferirConductores();
    imprimirReporteConductores("Reporte1.txt");
    /* Pregunta 2 */
    transferirInfracciones();
    imprimirReporteInfracciones("Reporte2.txt");
    /* Pregunta 3 */
    actualizarFaltas();
    actualizarConductores();
    imprimirReporte("Reporte3.txt");
    /* Pregunta 4 */
    actualizarFaltasAmnistia();
    actualizarConductores();
    imprimirReporte("Reporte4.txt");
    return 0;
}
