/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 10:08 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "AlumnoNota.h"
#include "Nota.h"
#include "Alumno.h"
#include "Funciones.h"
using namespace std;

#define MIN_APROBATORIO 11

void cargaralumnos(Alumno *lalumnos) {
    ifstream archAlumnos;
    abrirArchivoEntrada(archAlumnos, "Alumnos.csv");
    int numAlumnos = 0;
    while (true) {
        archAlumnos >> lalumnos[numAlumnos];
        if (archAlumnos.eof()) break;
        numAlumnos++;
    }
}

void carganotas(AlumnoNota *lnotas) {
    ifstream archNotas;
    abrirArchivoEntrada(archNotas, "Notas.csv");
    int numNotas = 0;
    while (true) {
        archNotas >> lnotas[numNotas];
        if (archNotas.eof()) break;
        numNotas++;
    }
}

void actualizanotas(Alumno *lalumnos, AlumnoNota *lnotas) {
    int posAlumno, posUltimaNota, veces;
    // Recorrer el arreglo de notas
    for (int i = 0; lnotas[i].GetCodigo(); i++) {
        posAlumno = buscarAlumno(lalumnos, lnotas[i].GetCodigo());
        if (posAlumno != NO_ENCONTRADO) {
            // Buscar si el curso ya fue procesado anteriormente en el arreglo
            if (cursoYaProcesado(lnotas, i)) continue;
            // Obtener el índice de la última nota que obtuvo el alumno
            obtenerUltimaNota(lnotas, i, posUltimaNota, veces);
            // Actualizar alumno con la última nota del curso
            agregarNota(lalumnos[posAlumno], lnotas[posUltimaNota], veces);
        }
    }
}

int buscarAlumno(Alumno *lalumnos, int codigo) {
    for (int i = 0; lalumnos[i].GetCodigo(); i++) {
        if (lalumnos[i].GetCodigo() == codigo) return i;
    }
    return NO_ENCONTRADO;
}

bool cursoYaProcesado(AlumnoNota *lnotas, int posNota) {
    for (int i = 0; i < posNota; i++) {
        if (esMismoAlumnoYCurso(lnotas[i], lnotas[posNota])) return true;
    }
    return false;
}

bool esMismoAlumnoYCurso(AlumnoNota &notaI, AlumnoNota &notaJ) {
    char codCursoI[MAX_CURSO], codCursoJ[MAX_CURSO];
    notaI.GetCodCurso(codCursoI);
    notaJ.GetCodCurso(codCursoJ);
    return notaI.GetCodigo() == notaJ.GetCodigo()
            and strcmp(codCursoI, codCursoJ) == 0;
}

void obtenerUltimaNota(AlumnoNota *lnotas, int posNota, int &posUltimaNota,
        int &veces) {
    int ultimoCiclo = 0;
    veces = 0;
    for (int i = posNota; lnotas[i].GetCodigo(); i++) {
        if (esMismoAlumnoYCurso(lnotas[i], lnotas[posNota])) {
            if (lnotas[i].GetCiclo() > ultimoCiclo) {
                ultimoCiclo = lnotas[i].GetCiclo();
                posUltimaNota = i;
            }
            veces++;
        }
    }
}

void agregarNota(Alumno &alumno, AlumnoNota &alumnoNota, int veces) {
    Nota nota;
    // Actualizar nota en el arreglo
    alumnoNota & nota;
    alumno += nota;
    // Actualizar contadores
    alumno.SetNumCursos(alumno.GetNumCursos() + 1);
    if (nota.GetNota() >= MIN_APROBATORIO) {
        alumno.SetNumAprobados(alumno.GetNumAprobados() + 1);
        switch (veces) {
            case 1:
                alumno.SetNumPrimera(alumno.GetNumPrimera() + 1);
                break;
            case 2:
                alumno.SetNumSegunda(alumno.GetNumSegunda() + 1);
                break;
            case 3:
                alumno.SetNumTercera(alumno.GetNumTercera() + 1);
                break;
        }
    }
}

void actualizanotas2(Alumno *lalumnos, AlumnoNota *lnotas) {
    int posAlumno, ultimaPosNota = NO_ENCONTRADO, veces;
    // Ordenar las notas para poder procesar rápidamente
    ordenarNotas(lnotas);
    pruebaOrdenamiento(lnotas);
    // Recorrer el arreglo de notas
    for (int i = 0; lnotas[i].GetCodigo(); i++) {
        // Ignorar si el código del alumno es igual a la última nota procesada
        if (ultimaPosNota != NO_ENCONTRADO and
                esMismoAlumnoYCurso(lnotas[i], lnotas[ultimaPosNota]))
            continue;
        // Buscar alumno en el listado
        posAlumno = buscarAlumno(lalumnos, lnotas[i].GetCodigo());
        if (posAlumno != NO_ENCONTRADO) {
            veces = obtenerNumVeces(lnotas, i);
            agregarNota(lalumnos[posAlumno], lnotas[i], veces);
        }
        // Actualizar última nota procesada
        ultimaPosNota = i;
    }
}

void ordenarNotas(AlumnoNota *lnotas) {
    int cantNotas;
    // Obtener la cantidad de notas
    for (cantNotas = 0; lnotas[cantNotas].GetCodigo(); cantNotas++);
    // Realizar el algoritmo de ordenamiento
    for (int i = 0; i < cantNotas-1; i++) {
        for (int j = i+1; j < cantNotas; j++) {
            if (verificarOrdenNotas(lnotas[i], lnotas[j])) {
                intercambiarObjeto(lnotas[i], lnotas[j]);
            }
        }
    }
}

bool verificarOrdenNotas(AlumnoNota &notaI, AlumnoNota &notaJ) {
    char codCursoI[MAX_CURSO], codCursoJ[MAX_CURSO];
    int result;
    // Ordenar ascendentemente por el código del alumno ascendentemente, por
    // el código del curso ascendentemente, y por el ciclo descendentemente
    if (notaI.GetCodigo() > notaJ.GetCodigo()) return true;
    if (notaI.GetCodigo() == notaJ.GetCodigo()) {
        notaI.GetCodCurso(codCursoI);
        notaJ.GetCodCurso(codCursoJ);
        result = strcmp(codCursoI, codCursoJ);
        if (result > 0 or (result == 0 and notaI.GetCiclo() < notaJ.GetCiclo()))
            return true;
    }
    return false;
}

void intercambiarObjeto(AlumnoNota &notaI, AlumnoNota &notaJ) {
    char codCursoI[MAX_CURSO], codCursoJ[MAX_CURSO];
    int aux;
    // Intercambiar código del alumno
    aux = notaI.GetCodigo();
    notaI.SetCodigo(notaJ.GetCodigo());
    notaJ.SetCodigo(aux);
    // Intercambiar código del curso
    notaI.GetCodCurso(codCursoI);
    notaJ.GetCodCurso(codCursoJ);
    notaI.SetCodCurso(codCursoJ);
    notaJ.SetCodCurso(codCursoI);
    // Intercambiar ciclo
    aux = notaI.GetCiclo();
    notaI.SetCiclo(notaJ.GetCiclo());
    notaJ.SetCiclo(aux);
    // Intercambiar nota
    aux = notaI.GetNota();
    notaI.SetNota(notaJ.GetNota());
    notaJ.SetNota(aux);
}

void pruebaOrdenamiento(AlumnoNota *lnotas) {
    ofstream arch;
    char codCurso[MAX_CURSO];
    abrirArchivoSalida(arch, "PruebaOrdenamiento.csv");
    for (int i = 0; lnotas[i].GetCodigo(); i++) {
        lnotas[i].GetCodCurso(codCurso);
        arch << lnotas[i].GetCodigo() << ',' << codCurso << ','
                << lnotas[i].GetCiclo() << ',' << lnotas[i].GetNota() << endl;
    }
}

int obtenerNumVeces(AlumnoNota *lnotas, int posNota) {
    int veces = 0;
    for (int i = posNota; lnotas[i].GetCodigo(); i++) {
        if (esMismoAlumnoYCurso(lnotas[i], lnotas[posNota])) veces++;
        else break;
    }
    return veces;
}

void imprimealumnos(Alumno *lalumnos) {
    ofstream archReporte;
    abrirArchivoSalida(archReporte, "Reporte.txt");
    archReporte << fixed << setprecision(2);
    for (int i = 0; lalumnos[i].GetCodigo(); i++) {
        archReporte << lalumnos[i] << endl;
    }
}

/* Funciones auxiliares */

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}
