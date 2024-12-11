/*
 * Archivo: Preg2_FuncionesDeHistoriaDeNotas.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de mayo de 2023, 09:51 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Preg1_FuncionesDeCursosYAlumnos.h"
#include "Preg2_FuncionesDeHistoriaDeNotas.h"
#include "AperturaDeArchivos.h"
#include "FuncionesAuxiliares.h"
using namespace std;

#define MAX_CURSO 10
#define MAX_NOTAS 10
#define NO_ENCONTRADO -1
#define TAM_LINEA_NOTAS 80

void cargarNotas(char ***&cursos_cod, int ***&cursos_nota_sem_veces,
        double **&costos, int **alumnos, char ***alumnos_nom_mod,
        double *escalas, char ***cursos, double *cursos_cred,
        const char *nomArchNotas) {
    ifstream archNotas;
    char *codCurso, car;
    int codAlumno, semestre, nota, posAlu, posCur;
    double monto;
    AperturaDeUnArchivoDeTextosParaLeer(archNotas, nomArchNotas);
    inicializarEspaciosNotas(cursos_cod, cursos_nota_sem_veces, costos, alumnos);
    // Leer línea por línea
    while (true) {
        archNotas >> codAlumno;
        if (archNotas.eof()) break;
        archNotas >> car;
        codCurso = leerCadenaDinamicaYExacta(archNotas, ',');
        archNotas >> semestre >> car >> nota;
        // Buscar alumno en el arreglo
        posCur = buscarCurso(cursos, codCurso);
        posAlu = buscarAlumno(alumnos, codAlumno);
        if (posCur != NO_ENCONTRADO && posAlu != NO_ENCONTRADO) {
            monto = calcularMonto(alumnos[posAlu], alumnos_nom_mod[posAlu],
                    escalas, cursos_cred[posCur]);
            agregarCursoEnAlumno(cursos_cod[posAlu], cursos_nota_sem_veces[posAlu],
                    costos[posAlu], codCurso, semestre, nota, monto);
        }
    }
    asignarEspaciosExactosNotas(cursos_cod, cursos_nota_sem_veces, costos);
}

void inicializarEspaciosNotas(char ***&cursos_cod,
        int ***&cursos_nota_sem_veces, double **&costos, int **alumnos) {
    int cantAlumnos;
    for (cantAlumnos = 0; alumnos[cantAlumnos]; cantAlumnos++);
    // Inicializar espacios de memoria principales
    cursos_cod = new char**[cantAlumnos+1]{};
    cursos_nota_sem_veces = new int**[cantAlumnos+1]{};
    costos = new double*[cantAlumnos+1]{};
    // Inicializar espacios de memoria secundarios
    for (int i = 0; i < cantAlumnos; i++) {
        cursos_cod[i] = new char*[MAX_NOTAS]{};
        cursos_nota_sem_veces[i] = new int*[MAX_NOTAS]{};
        costos[i] = new double[MAX_NOTAS]{};
    }
}

int buscarCurso(char ***cursos, char *codCurso) {
    char **auxCurso;
    for (int i = 0; cursos[i]; i++) {
        auxCurso = cursos[i];
        if (strcmp(auxCurso[COD_CURSO], codCurso) == 0)
            return i;
    }
    return NO_ENCONTRADO;
}

int buscarAlumno(int **alumnos, int codAlumno) {
    int *auxAlumno;
    for (int i = 0; alumnos[i]; i++) {
        auxAlumno = alumnos[i];
        if (auxAlumno[COD_ALUMNO] == codAlumno)
            return i;
    }
    return NO_ENCONTRADO;
}

double calcularMonto(int *alumno, char **alumnoNomMod, double *escalas,
        double creditos) {
    int posEscala = alumno[ESCALA]-1;
    double monto = escalas[posEscala] * creditos;
    char *modalidad = alumnoNomMod[MODALIDAD];
    switch (*modalidad) {
        case 'S': // Tener cuidado con las divisiones enteras
            monto *= (100-alumno[PORCENTAJE])/(double)100;
            break;
        case 'V': // Este caso se mencionó durante el examen
            monto *= 0.45;
            break;
    }
    return monto;
}

void agregarCursoEnAlumno(char **cursoCod, int **cursoNotaSemVeces,
        double *costo, char *codigo, int semestre, int nota, double monto) {
    int cantCurEnAlu, posCurEnAlu, *auxNotaSemVeces;
    // Obtener cantidad de cursos en alumnos
    for (cantCurEnAlu = 0; cursoCod[cantCurEnAlu]; cantCurEnAlu++);
    // Buscar si el alumno ya llevó el curso anteriormente
    posCurEnAlu = buscarCursoLlevadoPorAlumno(cursoCod, codigo);
    if (posCurEnAlu != NO_ENCONTRADO) {
        delete[] codigo; // Ya no vamos a usar esta cadena dinámica
        auxNotaSemVeces = cursoNotaSemVeces[posCurEnAlu];
        if (semestre > auxNotaSemVeces[SEMESTRE]) {
            auxNotaSemVeces[NOTA] = nota;
            auxNotaSemVeces[SEMESTRE] = semestre;
        }
        auxNotaSemVeces[VECES]++;
        costo[posCurEnAlu] += monto;
        costo[cantCurEnAlu] += monto;
    } else {
        cursoCod[cantCurEnAlu] = codigo;
        auxNotaSemVeces = new int[3];
        auxNotaSemVeces[NOTA] = nota;
        auxNotaSemVeces[SEMESTRE] = semestre;
        auxNotaSemVeces[VECES] = 1;
        cursoNotaSemVeces[cantCurEnAlu] = auxNotaSemVeces;
        // El nuevo total se moverá a la posición siguiente al nuevo curso
        costo[cantCurEnAlu+1] = costo[cantCurEnAlu] + monto;
        costo[cantCurEnAlu] = monto;
    }
}

int buscarCursoLlevadoPorAlumno(char **cursoCod, char *codCurso) {
    for (int i = 0; cursoCod[i]; i++) {
        if (strcmp(cursoCod[i], codCurso) == 0)
            return i;
    }
    return NO_ENCONTRADO;
}

void asignarEspaciosExactosNotas(char ***cursos_cod,
        int ***cursos_nota_sem_veces, double **costos) {
    int cantCursos, **auxNotaSemVeces;
    char **auxCursosCod;
    double *auxCostos;
    for (int i = 0; cursos_cod[i]; i++) {
        // Obtener cantidad de cursos por alumno
        for (cantCursos = 0; cursos_cod[cantCursos]; cantCursos++);
        // Asignar espacios de memoria exactos
        auxCursosCod = new char*[cantCursos+1]{};
        auxNotaSemVeces = new int*[cantCursos+1]{};
        auxCostos = new double[cantCursos+1]{};
        copiarDatosNotas(cursos_cod[i], cursos_nota_sem_veces[i], costos[i],
                auxCursosCod, auxNotaSemVeces, auxCostos, cantCursos);
        delete[] cursos_cod[i];
        delete[] cursos_nota_sem_veces[i];
        delete[] costos[i];
        cursos_cod[i] = auxCursosCod;
        cursos_nota_sem_veces[i] = auxNotaSemVeces;
        costos[i] = auxCostos;
    }
}

void copiarDatosNotas(char **cursoCod, int **cursoNotaSemVeces, double *costo,
        char **auxCursosCod, int **auxNotaSemVeces, double *auxCostos,
        int cantCursos) {
    for (int k = 0; k < cantCursos; k++) {
        auxCursosCod[k] = cursoCod[k];
        auxNotaSemVeces[k] = cursoNotaSemVeces[k];
        auxCostos[k] = costo[k];
    }
    // También se debe copiar el monto total gastado por el alumno
    auxCostos[cantCursos] = costo[cantCursos];
}

void pruebaDeCargaDeNotas(char ***cursos_cod, int ***cursos_nota_sem_veces,
        double **costos, int **alumnos, char ***alumnos_nom_mod,
        const char *nomArchRep) {
    ofstream archRep;
    AperturaDeUnArchivoDeTextosParaEscribir(archRep, nomArchRep);
    archRep << fixed << setprecision(2);
    // Imprimir cabecera del archivo
    archRep << right << setw(52) << "PRUEBA DE CARGA DE NOTAS" << endl;
    imprimirLinea(archRep, '=', TAM_LINEA_NOTAS);
    // Imprimir listado de alumnos
    for (int i = 0; alumnos[i]; i++) {
        imprimirAlumnoParaReporteNotas(archRep, alumnos[i], alumnos_nom_mod[i]);
        imprimirListaNotas(archRep, cursos_cod[i], cursos_nota_sem_veces[i],
                costos[i]);
        imprimirResumenNotas(archRep, cursos_cod[i], costos[i]);
    }
}

void imprimirAlumnoParaReporteNotas(ofstream &archRep, int *alumno,
        char **alumnoNomMod) {
    // Imprimir datos del alumno
    archRep << left << setw(12) << "CODIGO" << "NOMBRE" << endl;
    archRep << setw(12) << alumno[COD_ALUMNO] << alumnoNomMod[NOM_ALUMNO] << endl;
    imprimirLinea(archRep, '-', TAM_LINEA_NOTAS);
    // Imprimir cabecera de notas
    archRep << setw(10) << "CODIGO" << setw(15) << "ULTIMA NOTA"
            << setw(19) << "ULTIMO SEMESTRE" << setw(14) << "NRO. VECES"
            << "COSTO POR CURSO" << endl;
}

void imprimirListaNotas(ofstream &archRep, char **cursoCod,
        int **cursoNotaSemVeces, double *costo) {
    int *auxNotaSemVeces, anio, periodo;
    for (int k = 0; cursoCod[k]; k++) {
        auxNotaSemVeces = cursoNotaSemVeces[k];
        anio = auxNotaSemVeces[SEMESTRE] / 100;
        periodo = auxNotaSemVeces[SEMESTRE] % 100;
        archRep << left << setw(15) << cursoCod[k] << right << setfill('0')
                << setw(2) << auxNotaSemVeces[NOTA] << setfill(' ')
                << setw(17) << anio << '-' << periodo << setw(14)
                << auxNotaSemVeces[VECES] << setw(19) << costo[k] << endl;
    }
    imprimirLinea(archRep, '-', TAM_LINEA_NOTAS);
}

void imprimirResumenNotas(ofstream &archRep, char **cursoCod, double *costo) {
    int numCursos;
    for (numCursos = 0; cursoCod[numCursos]; numCursos++);
    archRep << "TOTAL GASTADO POR EL ALUMNO: " << setw(40)
            << costo[numCursos] << endl;
    imprimirLinea(archRep, '=', TAM_LINEA_NOTAS);
}
