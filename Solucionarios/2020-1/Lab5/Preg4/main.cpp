/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "Reserva.h"

int main() {
    Reserva reserva;
    reserva.carga("Aulas.csv", "Miembros.csv");
    reserva.asigna(4);
    reserva.imprime("Reporte.txt");
    return 0;
}
