/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:20 PM
 */

#include "Tienda.h"

int main() {
    Tienda tien;
    tien.carga();
    tien.actualiza(20);
    tien.muestra();
    return 0;
}
