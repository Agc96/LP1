/* 
 * Archivo: Sobrecarga.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include "Sobrecarga.h"
using namespace std;

#define MAX_LINEA 120
#define MAX_CICLOS 50

ifstream& operator >>(ifstream& arch, Alumno& alumno) {
    char tipo, nombre[MAX_LINEA];
    int codigo;
    // Leer los datos del alumno
    arch >> tipo >> codigo >> ws;
    if (arch.eof()) return arch;
    arch.getline(nombre, MAX_LINEA, ' ');
    while (arch.get() != '\n');
    // Guardar los datos en el objeto del alumno
    alumno.SetTipo(tipo);
    alumno.SetCodigo(codigo);
    alumno.SetNombre(nombre);
    alumno.SetNumcur(0);
    // Devolver el archivo de entrada para seguir operando
    return arch;
}

ofstream& operator <<(ofstream& arch, Alumno& alumno) {
    Curso curso;
    // Imprimir la cabecera
    arch << fixed << setprecision(2);
    arch << "Nombre: " << alumno.GetNombre() << endl;
    arch << "Código: " << alumno.GetCodigo() << endl;
    separacion(arch, '=');
    // Obtener lista de ciclos
    int ciclos[MAX_CICLOS] = {0}, numCiclos = 0;
    for (int i = 0; i < alumno.GetNumcur(); i++) {
        curso = alumno.GetLcursoAt(i);
        bool encontrado = false;
        for (int j = 0; j < numCiclos; j++) {
            if (ciclos[j] == curso.GetCiclo()) {
                encontrado = true;
            }
        }
        if (!encontrado) {
            ciclos[numCiclos++] = curso.GetCiclo();
        }
    }
    // Imprimir lita de ciclos
    if (numCiclos > 0) {
        arch << setw(15) << "CICLO" << setw(20) << "PROMEDIO" << endl;
        for (int k = 0; k < numCiclos; k++) {
            arch << setw(4) << (k+1) << ')';
            arch << setw(8) << (ciclos[k]/10) << '-' << (ciclos[k]%10);
            arch << setw(20) << (alumno/ciclos[k]) << endl;
        }
        arch << endl;
    }
    // Imprimir las estadísticas
    arch << "Créditos Cursados: " << setw(10) << (--alumno) << endl;
    arch << "Créditos Aprobados:" << setw(10) << (++alumno) << endl;
    // Devolver el archivo de salida para seguir operando
    return arch;
}

ifstream& operator >>(ifstream& arch, ACurso& acurso) {
    char ccurso[MAX_LINEA], operacion, c;
    int codigo, nota, anho, periodo;
    double credito;
    Curso curso;
    // Leer los datos del alumno-curso
    arch >> codigo >> ws;
    if (arch.eof()) return arch;
    arch.getline(ccurso, MAX_LINEA, ' ');
    arch >> nota >> anho >> c >> periodo >> credito >> ws >> operacion;
    // Guardar los datos del curso
    curso.SetCcurso(ccurso);
    curso.SetCiclo(anho*10 + periodo);
    curso.SetNota(nota);
    curso.SetCredito(credito);
    // Guardar los datos del alumno-curso
    acurso.SetCurso(curso);
    acurso.SetCodigo(codigo);
    acurso.SetOperacion(operacion);
    // Devolver el archivo de entrada para seguir operando
    return arch;
}

void separacion(ofstream& arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        arch.put(c);
    }
    arch << endl;
}
