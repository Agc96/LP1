/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "FuncionesPreg2.h"
#define MAX_ALUMNOS 100

int main(int argc, char** argv) {
    Alumno alumnos[MAX_ALUMNOS];
    int numAlumnos = leerAlumnos(alumnos);
    leerCursos(alumnos, numAlumnos, "Cursos.txt");
    leerCursos(alumnos, numAlumnos, "Correcciones.txt");
    consolidado(alumnos, numAlumnos);
    return 0;
}
