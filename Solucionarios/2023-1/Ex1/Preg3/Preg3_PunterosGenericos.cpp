/*
 * Archivo: Preg3_PunterosGenericos.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de mayo de 2023, 06:52 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Preg3_PunterosGenericos.h"
#include "AperturaDeArchivos.h"
#include "FuncionesAuxiliares.h"
using namespace std;

#define MAX_NOTAS 10
#define NO_ENCONTRADO -1

void CargaCursos(int *alumnos_cod, void *&alumnoveces,
        const char *nomArchNotas) {
    ifstream archNotas;
    char *codCurso, car;
    int codAlumno, semestre, nota, posAlumno;
    void *curso;
    AperturaDeUnArchivoDeTextosParaLeer(archNotas, nomArchNotas);
    inicializarAlumnoVeces(alumnos_cod, alumnoveces);
    // Leer línea por línea
    while (true) {
        archNotas >> codAlumno;
        if (archNotas.eof()) break;
        archNotas >> car;
        codCurso = leerCadenaDinamicaYExacta(archNotas, ',');
        archNotas >> semestre >> car >> nota;
        // Crear registro del curso
        curso = crearPunteroGenericoCurso(codCurso, semestre, nota);
        // Buscar el alumno en el listado de códigos
        posAlumno = buscarAlumnoCod(alumnos_cod, codAlumno);
        if (posAlumno != NO_ENCONTRADO)
            agregarCursoEnAlumno(alumnoveces, posAlumno, curso);
    }
    asignarEspaciosExactosAListaCursos(alumnoveces);
}

void inicializarAlumnoVeces(int *alumnos_cod, void *&alumnoveces) {
    int cantAlumnos;
    void **auxAlumnoVeces, **alumno;
    // Obtener cantidad de alumnos
    for (cantAlumnos = 0; alumnos_cod[cantAlumnos]; cantAlumnos++);
    // Asignar espacios de memoria
    auxAlumnoVeces = new void*[cantAlumnos+1]{};
    for (int i = 0; i < cantAlumnos; i++) {
        alumno = new void*[7]{};
        alumno[COD_ALUMNO_AV] = new int(alumnos_cod[i]);
        alumno[CURSOS_TOTAL] = new int(0);
        alumno[CURSOS_APROB] = new int(0);
        alumno[CURSOS_1RA] = new int(0);
        alumno[CURSOS_2DA] = new int(0);
        alumno[CURSOS_3RA] = new int(0);
        auxAlumnoVeces[i] = alumno;
    }
    alumnoveces = auxAlumnoVeces;
}

void *crearPunteroGenericoCurso(char *codCurso, int semestre, int nota) {
    void **curso = new void*[3];
    curso[COD_CURSO_AV] = codCurso;
    curso[SEMESTRE] = new int(semestre);
    curso[NOTA] = new int(nota);
    return curso;
}

int buscarAlumnoCod(int *alumnos_cod, int codigo) {
    for (int i = 0; alumnos_cod[i]; i++) {
        if (alumnos_cod[i] == codigo)
            return i;
    }
    return NO_ENCONTRADO;
}

void agregarCursoEnAlumno(void *alumnoveces, int posAlumno, void *nuevoCurso) {
    void **auxAlumnoVeces, **alumno, **listaCursos;
    int numCursos, *auxCursosTotal;
    // Ubicar el alumno en el puntero genérico
    auxAlumnoVeces = (void **)alumnoveces;
    alumno = (void **)(auxAlumnoVeces[posAlumno]);
    // Actualizar la cantidad de cursos
    auxCursosTotal = (int *)(alumno[CURSOS_TOTAL]);
    (*auxCursosTotal)++;
    // Verificar si el alumno tiene creada la lista de cursos
    if (alumno[CURSOS_LISTA]) {
        listaCursos = (void **)(alumno[CURSOS_LISTA]);
        // Obtener la cantidad de cursos y agregar el nuevo curso al final
        for (numCursos = 0; listaCursos[numCursos]; numCursos++);
        listaCursos[numCursos] = nuevoCurso;
    } else {
        listaCursos = new void*[MAX_NOTAS]{};
        listaCursos[0] = nuevoCurso;
        alumno[CURSOS_LISTA] = listaCursos;
    }
}

void asignarEspaciosExactosAListaCursos(void *alumnoveces) {
    void **auxAlumnoVeces, **alumno, **listaCursos, **auxListaCursos;
    int numCursos;
    // Recorrer alumno por alumno
    auxAlumnoVeces = (void **)alumnoveces;
    for (int i = 0; auxAlumnoVeces[i]; i++) {
        alumno = (void **)(auxAlumnoVeces[i]);
        listaCursos = (void **)(alumno[CURSOS_LISTA]);
        if (listaCursos == nullptr) continue;
        // Obtener cantidad de cursos
        for (numCursos = 0; listaCursos[numCursos]; numCursos++);
        // Asignar espacios exactos a la lista de cursos
        auxListaCursos = new void*[numCursos+1]{};
        for (int k = 0; k < numCursos; k++)
            auxListaCursos[k] = listaCursos[k];
        delete[] listaCursos;
        alumno[CURSOS_LISTA] = auxListaCursos;
    }
}

void ActualizaVeces(void *alumnoveces) {
    void **auxAlumnoVeces, **alumno, **listaCursos, **auxCurso;
    int nota, veces;
    char *codCurso;
    // Recorrer alumno por alumno
    auxAlumnoVeces = (void **)alumnoveces;
    for (int i = 0; auxAlumnoVeces[i]; i++) {
        alumno = (void **)(auxAlumnoVeces[i]);
        listaCursos = (void **)(alumno[CURSOS_LISTA]);
        if (listaCursos == nullptr) continue;
        // Buscar curso por curso
        for (int posCurso = 0; listaCursos[posCurso]; posCurso++) {
            auxCurso = (void **)(listaCursos[posCurso]);
            codCurso = (char *)(auxCurso[COD_CURSO_AV]);
            // Si el curso ya fue procesado anteriormente ignorarlo
            if (cursoYaProcesado(listaCursos, posCurso, codCurso)) continue;
            // Buscar en el resto del arreglo la última nota obtenida en el curso
            buscarUltimaNotaCurso(listaCursos, posCurso, codCurso, nota, veces);
            // Actualizar las estadísticas usando la última nota obtenida
            actualizarEstadisticas(alumno, nota, veces);
        }
    }
}

bool cursoYaProcesado(void **listaCursos, int posCurso, char *codBuscado) {
    char *codLeido;
    void **auxCurso;
    for (int k = 0; k < posCurso; k++) {
        auxCurso = (void **)(listaCursos[k]);
        codLeido = (char *)(auxCurso[COD_CURSO_AV]);
        if (strcmp(codLeido, codBuscado) == 0) return true;
    }
    return false;
}

void buscarUltimaNotaCurso(void **listaCursos, int posCurso, char *codBuscado,
        int &ultimaNota, int &vecesCurso) {
    char *codLeido;
    int ultimoSemestre = 0, *auxSemestre, *auxNota;
    void **auxCurso;
    vecesCurso = 0;
    ultimaNota = 0;
    for (int k = posCurso; listaCursos[k]; k++) {
        auxCurso = (void **)(listaCursos[k]);
        codLeido = (char *)(auxCurso[COD_CURSO_AV]);
        if (strcmp(codLeido, codBuscado) == 0) {
            auxSemestre = (int *)(auxCurso[SEMESTRE]);
            if (*auxSemestre > ultimoSemestre) {
                ultimoSemestre = *auxSemestre;
                auxNota = (int *)(auxCurso[NOTA]);
                ultimaNota = *auxNota;
            }
            vecesCurso++;
        }
    }
}

void actualizarEstadisticas(void **alumno, int nota, int veces) {
    int *estadistica;
    if (nota > 10) {
        switch (veces) {
            case 1:
                estadistica = (int *)(alumno[CURSOS_1RA]);
                (*estadistica)++;
                break;
            case 2:
                estadistica = (int *)(alumno[CURSOS_2DA]);
                (*estadistica)++;
                break;
            case 3:
                estadistica = (int *)(alumno[CURSOS_3RA]);
                (*estadistica)++;
                break;
        }
        estadistica = (int *)(alumno[CURSOS_APROB]);
        (*estadistica)++;
    }
}
