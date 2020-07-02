/* 
 * Archivo: FuncionesPreg1.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include "Curso.h"
#include "Alumno.h"
#include "ACurso.h"
#include "Sobrecarga.h"
#include "FuncionesPreg2.h"
using namespace std;

int leerAlumnos(Alumno* alumnos) {
    int numAlumnos = 0;
    // Leer los datos del alumno
    ifstream archAlu("Alumnos.txt", ios::in);
    if (!archAlu) {
        cerr << "No se pudo abrir el archivo de alumnos." << endl;
        exit(1);
    }
    /* Leer línea por línea los datos de los alumnos */
    while (true) {
        archAlu >> alumnos[numAlumnos];
        if (archAlu.eof()) break;
        numAlumnos++;
    }
    return numAlumnos;
}

void leerCursos(Alumno* alumnos, int numAlumnos, const char* nomArch) {
    ACurso acurso;
    // Leer los datos del alumno-curso
    ifstream archCur(nomArch, ios::in);
    if (!archCur) {
        cerr << "No se pudo abrir el archivo " << nomArch << '.' << endl;
        exit(1);
    }
    while (true) {
        archCur >> acurso;
        if (archCur.eof()) break;
        // Agregar, actualizar o eliminar dependiendo del caso
        bool encontrado = false;
        for (int i = 0; i < numAlumnos; i++) {
            if (alumnos[i].GetCodigo() == acurso.GetCodigo()) {
                switch (acurso.GetOperacion()) {
                    case 'N':
                        (alumnos[i] + acurso);
                        break;
                    case 'A':
                        (alumnos[i] * acurso);
                        break;
                    case 'E':
                        (alumnos[i] - acurso);
                        break;
                    default:
                        cerr << "No se encontró la operación." << endl;
                }
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cerr << "No se encontró el alumno-curso." << endl;
        }
    }
}

void consolidado(Alumno* alumnos, int numAlumnos) {
    // Imprimir los datos del alumno
    ofstream archRep("Reporte.txt", ios::out);
    if (!archRep) {
        cerr << "No se pudo crear el archivo del reporte." << endl;
        exit(1);
    }
    for (int i = 0; i < numAlumnos; i++) {
        archRep << alumnos[i] << endl;
    }
}
