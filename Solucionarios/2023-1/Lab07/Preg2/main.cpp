/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:15 AM
 */

#include "Funciones.h"
#include "Alumno.h"
#include "AlumnoNota.h"

int main() {
    Alumno lalumnos[MAX_ALUMNOS];
    AlumnoNota lnotas[MAX_ALUMNONOTAS];
    cargaralumnos(lalumnos);
    carganotas(lnotas);
    /* He hecho dos versiones de actualizanotas:
     * - La primera sin ordenamiento, comparando para cada AlumnoNota en el
     *   arreglo, si hay notas del mismo alumno y curso descartarlo porque ya
     *   lo procesé, si hay notas del mismo alumno y curso buscar la nota del
     *   último ciclo que llevó dicho curso. Todo ello similar al algoritmo que
     *   propuse para el examen parcial.
     * - La segunda ordenando primero por alumno y curso de manera ascendente,
     *   y el ciclo de manera descendente, para poder acceder rápidamente a la
     *   última nota que sacó un alumno en un curso en específico (sugerencia
     *   del profesor Rony Cueva).
     * Si se quiere probar la segunda versión, basta colocar actualizanotas2
     * en vez de actualizanotas. Ambas funciones producen el mismo resultado. */
    actualizanotas(lalumnos, lnotas);
    imprimealumnos(lalumnos);
    return 0;
}
