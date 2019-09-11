/*
 * File: utils.cpp
 * Author: Anthony Gutiérrez (20130095)
 */

#ifndef UTILS_H
#define UTILS_H

#define MAX_LINEA 100
#define MAX_EMPLEADO 40
#define SEP_FECHA (10 + MAX_EMPLEADO + 9)
#define SEP_TIEMPO (SEP_FECHA + 12)

void separacion(char, int);
void espacio(int);
void cabecera(int, int, int, int, int, int);
void imprimirFecha(int, int, int, bool);
void imprimirHora(double, bool);

#endif /* UTILS_H */

