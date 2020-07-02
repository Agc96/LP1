/* 
 * Archivo: FuncionesPreg1.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include "Curso.h"
#include "Alumno.h"
#include "ACurso.h"
#include "Sobrecarga.h"
#include "FuncionesPreg1.h"
using namespace std;

void leerAlumno(Alumno& alumno) {
    // Leer los datos del alumno
    ifstream archAlu("Alumnos.txt", ios::in);
    if (!archAlu) {
        cerr << "No se pudo abrir el archivo de alumnos." << endl;
        exit(1);
    }
    archAlu >> alumno;
    // Imprimir los datos del alumno
    ofstream archRep("Reporte.txt", ios::out);
    if (!archRep) {
        cerr << "No se pudo crear el archivo del reporte." << endl;
        exit(1);
    }
    archRep << alumno << endl;
}

void leerCursos(Alumno& alumno, const char* nomArch) {
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
        char operacion = acurso.GetOperacion();
        switch (operacion) {
            case 'N':
                alumno + acurso;
                break;
            case 'A':
                alumno * acurso;
                break;
            case 'E':
                alumno - acurso;
                break;
            default:
                cerr << "No se encontró la operación " << operacion << endl;
        }
    }
    // Imprimir los datos del alumno
    ofstream archRep("Reporte.txt", ios::app);
    if (!archRep) {
        cerr << "No se pudo abrir el archivo del reporte." << endl;
        exit(1);
    }
    archRep << alumno << endl;
}
