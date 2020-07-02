/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "FuncionesPreg1.h"

int main(int argc, char** argv) {
    Alumno alumno;
    leerAlumno(alumno);
    leerCursos(alumno, "Cursos.txt");
    leerCursos(alumno, "Correcciones.txt");
    return 0;
}
