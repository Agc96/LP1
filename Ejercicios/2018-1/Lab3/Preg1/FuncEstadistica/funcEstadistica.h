/* 
 * Archivo: funcEstadistica.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 19 de septiembre de 2019, 03:24 PM
 */

#ifndef FUNCESTADISTICA_H
#define FUNCESTADISTICA_H

template <typename T> double mediaAritmetica(T[], int);
template <typename T1, typename T2> double mediaPonderada(T1[], T2[], int);
template <typename T> T mediana(T[], int);
template <typename T> void ordenar(T[], int, int);
template <typename T> void cambiar(T[], int, int);
template <typename T> double desvEstandar(T[], int);
template <typename T1, typename T2> int distFrecuencias(T1[], int, T2[], int,
        int[]);

#endif /* FUNCESTADISTICA_H */
