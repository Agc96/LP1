/* 
 * Archivo: funcEstadistica.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Created on 19 de septiembre de 2019, 03:24 PM
 */

#include <cmath>
#include "funcEstadistica.h"

#define MAX_DATOS 500
#define MAX_FRECUENCIAS 20

template <typename T>
double mediaAritmetica(T datos[], int numDatos) {
    double sumaDatos = 0;
    for (int i = 0; i < numDatos; i++) {
        sumaDatos += datos[i];
    }
    return sumaDatos / numDatos;
}

template <typename T1, typename T2>
double mediaPonderada(T1 datos[], T2 pesos[], int numDatos) {
    double sumaPonderada = 0, sumaPesos = 0;
    for (int i = 0; i < numDatos; i++) {
        sumaPonderada += datos[i] * pesos[i];
        sumaPesos += pesos[i];
    }
    return sumaPonderada / sumaPesos;
}


template <typename T>
T mediana(T datos[], int numDatos) {
    // Copiar datos del arreglo
    T auxiliar[MAX_DATOS];
    for (int i = 0; i < numDatos; i++) {
        auxiliar[i] = datos[i];
    }
    // Ordenar los datos del arreglo
    ordenar(auxiliar, 0, numDatos - 1);
    // Devolver el elemento ubicado en la mitad del arreglo
    return auxiliar[numDatos/2];
}

template <typename T>
void ordenar(T arreglo[], int izquierda, int derecha) {
    if (izquierda >= derecha) return;
    // Elegir un elemento del arreglo como pivote
    cambiar(arreglo, izquierda, (izquierda + derecha) / 2);
    int limite = izquierda;
    // Resituar los demás elementos de la lista a cada lado del pivote
    for (int i = izquierda + 1; i <= derecha; i++) {
        if (arreglo[i] < arreglo[izquierda]) {
            cambiar(arreglo, ++limite, i);
        }
    }
    // El pivote ocupará exactamente el lugar que le corresponderá
    cambiar(arreglo, izquierda, limite);
    // Repetir este proceso de forma recursiva para cada sección del arreglo
    ordenar(arreglo, izquierda, limite - 1);
    ordenar(arreglo, limite + 1, derecha);
}

template <typename T>
void cambiar(T arreglo[], int izquierda, int derecha) {
    T auxiliar = arreglo[izquierda];
    arreglo[izquierda] = arreglo[derecha];
    arreglo[derecha] = auxiliar;
}

template <typename T>
double desvEstandar(T datos[], int numDatos) {
    double media = mediaAritmetica(datos, numDatos), sumaDistancias = 0;
    for (int i = 0; i < numDatos; i++) {
        sumaDistancias += pow(datos[i] - media, 2);
    }
    return sqrt(sumaDistancias / (numDatos - 1));
}

template <typename T1, typename T2>
int distFrecuencias(T1 datos[], int numDatos, T2 limites[], int numLimites,
        int frecuencias[]) {
    for (int i = 0; i <= numLimites; i++) {
        frecuencias[i] = 0;
    }
    for (int i = 0; i < numDatos; i++) {
        bool pendienteAgregar = true;
        for (int j = 0; pendienteAgregar && j < numLimites; j++) {
            if (datos[i] <= limites[j]) {
                frecuencias[j]++;
                pendienteAgregar = false;
            }
        }
        if (pendienteAgregar) {
            frecuencias[numLimites]++;
        }
    }
    return (numLimites + 1);
}

template double mediaAritmetica(int[], int);
template double mediaAritmetica(double[], int);

template double mediaPonderada(int[], int[], int);
template double mediaPonderada(int[], double[], int);
template double mediaPonderada(double[], double[], int);
template double mediaPonderada(double[], int[], int);

template int mediana(int[], int);
template double mediana(double[], int);

template void ordenar(int[], int, int);
template void ordenar(double[], int, int);

template void cambiar(int[], int, int);
template void cambiar(double[], int, int);

template double desvEstandar(int[], int);
template double desvEstandar(double[], int);

template int distFrecuencias(int[], int, int[], int, int[]);
template int distFrecuencias(int[], int, double[], int, int[]);
template int distFrecuencias(double[], int, int[], int, int[]);
template int distFrecuencias(double[], int, double[], int, int[]);
