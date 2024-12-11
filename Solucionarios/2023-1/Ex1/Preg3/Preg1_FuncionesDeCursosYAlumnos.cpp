/*
 * Archivo: Preg1_FuncionesDeCursosYAlumnos.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de mayo de 2023, 08:57 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Preg1_FuncionesDeCursosYAlumnos.h"
#include "AperturaDeArchivos.h"
#include "FuncionesAuxiliares.h"
using namespace std;

#define INCREMENTO 5
#define TAM_LINEA_CURSOS 120
#define TAM_LINEA_ALUMNOS 90

void cargarCursosYEscalas(char ***&cursos, double *&cursos_cred, double *escalas,
        const char *nomArchCursos, const char *nomArchEscalas) {
    ifstream archCursos, archEscalas;
    AperturaDeUnArchivoDeTextosParaLeer(archCursos, nomArchCursos);
    AperturaDeUnArchivoDeTextosParaLeer(archEscalas, nomArchEscalas);
    cargarCursos(archCursos, cursos, cursos_cred);
    cargarEscalas(archEscalas, escalas);
}

void cargarCursos(ifstream &archCursos, char ***&cursos,
        double *&cursos_cred) {
    char *codCurso, *nomCurso, *nomProfe, **auxCurso, car;
    int numCursos = 0, tamCursos = 0, codProfe;
    double credCurso;
    // Leer línea por línea
    while (true) {
        codCurso = leerCadenaDinamicaYExacta(archCursos, ',');
        if (codCurso == nullptr) break;
        nomCurso = leerCadenaDinamicaYExacta(archCursos, ',');
        archCursos >> credCurso >> car >> codProfe >> car;
        nomProfe = leerCadenaDinamicaYExacta(archCursos, '\n');
        // Guardar datos del curso
        if (numCursos == tamCursos)
            incrementarEspaciosCursos(cursos, cursos_cred, numCursos, tamCursos);
        auxCurso = new char*[3];
        auxCurso[COD_CURSO] = codCurso;
        auxCurso[NOM_CURSO] = nomCurso;
        auxCurso[NOM_PROFE] = nomProfe;
        cursos[numCursos-1] = auxCurso;
        cursos_cred[numCursos-1] = credCurso;
        numCursos++;
    }
}

void incrementarEspaciosCursos(char ***&cursos, double *&cursos_cred,
        int &numCursos, int &tamCursos) {
    char ***auxCursos;
    double *auxCursosCred;
    tamCursos += INCREMENTO;
    if (numCursos == 0) {
        cursos = new char**[tamCursos]{};
        cursos_cred = new double[tamCursos]{};
        numCursos = 1;
    } else {
        auxCursos = new char**[tamCursos]{};
        auxCursosCred = new double[tamCursos]{};
        for (int i = 0; i < numCursos; i++) {
            auxCursos[i] = cursos[i];
            auxCursosCred[i] = cursos_cred[i];
        }
        delete[] cursos;
        delete[] cursos_cred;
        cursos = auxCursos;
        cursos_cred = auxCursosCred;
    }
}

void cargarEscalas(ifstream &archEscalas, double *escalas) {
    char car;
    int indice;
    double monto;
    // Leer línea por línea
    while (true) {
        archEscalas >> car;
        if (archEscalas.eof()) break;
        archEscalas >> indice >> car >> monto;
        // Guardar monto de la escala
        escalas[indice-1] = monto;
    }
}

void pruebaDeCargaDeCursos(char ***cursos, double *cursos_cred,
        const char *nomArchRep) {
    ofstream archRep;
    char **auxCurso;
    AperturaDeUnArchivoDeTextosParaEscribir(archRep, nomArchRep);
    archRep << fixed << setprecision(2);
    // Imprimir cabecera del archivo
    archRep << right << setw(62) << "PRUEBA DE CARGA DE CURSOS" << endl;
    imprimirLinea(archRep, '=', TAM_LINEA_CURSOS);
    archRep << left << setw(10) << "CODIGO" << setw(55) << "NOMBRE"
            << setw(40) << "PROFESOR" << "CREDITOS" << endl;
    // Imprimir datos de los cursos
    for (int i = 0; cursos[i]; i++) {
        auxCurso = cursos[i];
        archRep << setw(10) << auxCurso[COD_CURSO] << setw(55)
                << auxCurso[NOM_CURSO] << setw(40) << auxCurso[NOM_PROFE]
                << cursos_cred[i] << endl;
    }
}

void cargarAlumnos(int *&alumnos_cod, int **&alumnos, char ***&alumnos_nom_mod,
        const char *nomArchAlumnos) {
    ifstream archAlumnos;
    char *nombre, modalidad, car, **alumnoNomMod;
    int numAlumnos = 0, tamAlumnos = 0, codigo, porcentaje, escala, *alumno;
    AperturaDeUnArchivoDeTextosParaLeer(archAlumnos, nomArchAlumnos);
    // Leer línea por línea
    while (true) {
        archAlumnos >> codigo >> car;
        if (archAlumnos.eof()) break;
        nombre = leerCadenaDinamicaYExacta(archAlumnos, ',');
        leerModalidadAlumno(archAlumnos, modalidad, porcentaje, escala);
        // Guardar datos de los alumnos
        if (numAlumnos == tamAlumnos)
            incrementarEspaciosAlumnos(alumnos_cod, alumnos, alumnos_nom_mod,
                    numAlumnos, tamAlumnos);
        crearNodosAlumno(codigo, escala, porcentaje, nombre, modalidad,
                alumno, alumnoNomMod);
        alumnos_cod[numAlumnos-1] = codigo;
        alumnos[numAlumnos-1] = alumno;
        alumnos_nom_mod[numAlumnos-1] = alumnoNomMod;
        numAlumnos++;
    }
}

void leerModalidadAlumno(ifstream &archAlumnos, char &modalidad,
        int &porcentaje, int &escala) {
    char car;
    archAlumnos >> modalidad;
    if (modalidad == 'S') {
        archAlumnos >> car >> porcentaje >> car >> car >> escala;
    } else if (modalidad == 'V') {
        archAlumnos >> car >> car >> escala;
    } else {
        archAlumnos >> escala;
        modalidad = 'P'; // Opcional, puede dejarse con el caracter original
    }
}

void incrementarEspaciosAlumnos(int *&alumnos_cod, int **&alumnos,
        char ***&alumnos_nom_mod, int &numAlumnos, int &tamAlumnos) {
    char ***auxAlumnosNomMod;
    int *auxAlumnosCod, **auxAlumnos;
    tamAlumnos += INCREMENTO;
    if (numAlumnos == 0) {
        alumnos_cod = new int[tamAlumnos]{};
        alumnos = new int*[tamAlumnos]{};
        alumnos_nom_mod = new char**[tamAlumnos]{};
        numAlumnos = 1;
    } else {
        auxAlumnosCod = new int[tamAlumnos]{};
        auxAlumnos = new int*[tamAlumnos]{};
        auxAlumnosNomMod = new char**[tamAlumnos]{};
        for (int i = 0; i < numAlumnos; i++) {
            auxAlumnosCod[i] = alumnos_cod[i];
            auxAlumnos[i] = alumnos[i];
            auxAlumnosNomMod[i] = alumnos_nom_mod[i];
        }
        delete[] alumnos_cod;
        delete[] alumnos;
        delete[] alumnos_nom_mod;
        alumnos_cod = auxAlumnosCod;
        alumnos = auxAlumnos;
        alumnos_nom_mod = auxAlumnosNomMod;
    }
}

void crearNodosAlumno(int codigo, int escala, int porcentaje, char *nombre,
        char modalidad, int *&alumno, char **&alumnoNomMod) {
    // Crear nodo del código, escala y porcentaje del alumno
    if (modalidad == 'S') {
        alumno = new int[3];
        alumno[PORCENTAJE] = porcentaje;
    } else
        alumno = new int[2];
    alumno[COD_ALUMNO] = codigo;
    alumno[ESCALA] = escala;
    // Crear nodo del nombre y la modalidad del alumno
    alumnoNomMod = new char*[2];
    alumnoNomMod[NOM_ALUMNO] = nombre;
    alumnoNomMod[MODALIDAD] = new char(modalidad);
}

void pruebaDeCargaDeAlumnos(int *alumnos_cod, int **alumnos,
        char ***alumnos_nom_mod, const char *nomArchRep) {
    ofstream archRep;
    AperturaDeUnArchivoDeTextosParaEscribir(archRep, nomArchRep);
    archRep << fixed << setprecision(2);
    // Imprimir cabecera del archivo
    archRep << right << setw(58) << "PRUEBA DE CARGA DE ALUMNOS" << endl;
    imprimirLinea(archRep, '=', TAM_LINEA_ALUMNOS);
    archRep << left << setw(12) << "CODIGO" << setw(40) << "NOMBRE"
            << setw(12) << "MODALIDAD" << setw(13) << "PORCENTAJE"
            << "ESCALA" << endl;
    // Imprimir datos de los cursos
    for (int i = 0; alumnos_cod[i]; i++) {
        imprimirAlumno(archRep, alumnos[i], alumnos_nom_mod[i]);
    }
}

void imprimirAlumno(ofstream &archRep, int *auxAlumno, char **auxNomMod) {
    char *modalidad = auxNomMod[MODALIDAD];
    archRep << left << setw(12) << auxAlumno[COD_ALUMNO] << setw(40)
            << auxNomMod[NOM_ALUMNO] << setw(5) << right << *modalidad;
    if (*modalidad == 'S')
        archRep << setw(13) << auxAlumno[PORCENTAJE] << setw(11)
                << auxAlumno[ESCALA] << endl;
    else
        archRep << setw(24) << auxAlumno[ESCALA] << endl;
}
