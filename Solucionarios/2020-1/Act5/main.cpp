/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "FuncionesActividad05.h"

int main() {
    void* alumnos;
    leerAlumnos(alumnos);
    imprimirAlumnos(alumnos);
    leerCursos(alumnos);
    consolidado(alumnos);
    return 0;
}
