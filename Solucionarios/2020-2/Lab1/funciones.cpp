/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 18 de septiembre de 2020, 08:14 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "funciones.h"
using namespace std;

#define MAX_LINEA 120
#define MAX_NOMBRE 50
#define MAX_CODIGO 10
#define MIN_APROBADA 11

void procesarAlumnos() {
    int numAlumnos = 0, codigo;
    // Imprimir la cabecera del reporte
    cout << setw(80) << "INFORMACION ACADEMICA DE LOS ESTUDIANTES" << endl;
    separacion('=');
    // Leer alumno por alumno
    while (true) {
        cin >> codigo;
        if (cin.eof()) break;
        procesarAlumno(codigo);
        numAlumnos++;
    }
    // Imprimir el resumen del reporte
    cout << "TOTAL DE ALUMNOS REGISTRADOS: " << numAlumnos << endl;
}

void procesarAlumno(int codigo) {
    int numCursos = 0, numCurAprob = 0, numCurError = 0, contador = 0, anho;
    double credAprob = 0, credDesaprob = 0, sumaNotas = 0, sumaAprob = 0;
    char c, nombre[MAX_NOMBRE];
    // Leer e imprimir datos principales del alumno
    cin >> c >> anho >> ws >> nombre;
    imprimirCabeceraAlumno(codigo, anho, nombre);
    // Leer curso por curso
    while (true) {
        c = cin.peek();
        if (c == '\n') break;
        contador++;
        procesarCursoAlumno(anho, contador, numCursos, credAprob, credDesaprob,
                numCurAprob, numCurError, sumaNotas, sumaAprob);
    }
    // Imprimir resumen
    imprimirResumenAlumno(numCursos, credAprob, credDesaprob, numCurAprob,
            numCurError, sumaNotas, sumaAprob);
}

void imprimirCabeceraAlumno(int codigo, int anho, char* nombre) {
    // Procesar el nombre del alumno
    int i = 0;
    while (nombre[i] != '\0') {
        if (nombre[i] == '/' || nombre[i] == '-') nombre[i] = ' ';
        i++;
    }
    // Imprimir datos del alumno
    cout << left << setw(4) << ' ' << "Alumno: " << setw(50) << nombre;
    cout << "Codigo: " << anho << " - ";
    cout << right << setfill('0') << setw(6) << codigo << setfill(' ') << endl;
    separacion('-');
    // Imprimir cabecera de cursos aprobados y desaprobados
    cout << left << setw(15) << ' ' << setw(40) << "CURSOS APROBADOS";
    cout << setw(30) << "CURSOS DESAPROBADOS" << setw(20) << "OBSERVACION" << endl;
    cout << setw(40) << "No.  CODIGO  CREDITOS  NOTA  FECHA";
    cout << setw(40) << "     CODIGO  CREDITOS  NOTA  FECHA" << endl;
    separacion('-');
}

void procesarCursoAlumno(int anhoAlumno, int contador, int& numCursos, double& credAprob,
        double& credDesaprob, int& numCurAprob, int& numCursosError, double& sumaNotas,
        double& sumaAprob) {
    char c, codigo[MAX_CODIGO];
    int nota, dia, mes, anho;
    double creditos;
    // Leer e imprimir los datos del curso
    cin >> codigo >> creditos >> nota >> dia >> c >> mes >> c >> anho;
    imprimirCursoAlumno(contador, codigo, creditos, nota, dia, mes, anho);
    // Actualizar contadores
    if (anhoAlumno > anho) {
        cout << right << setw(18) << "ERROR FECHA" << endl;
        numCursosError++;
    } else {
        sumaNotas += nota;
        numCursos++;
        if (nota >= MIN_APROBADA) {
            credAprob += creditos;
            sumaAprob += nota;
            numCurAprob++;
        } else {
            credDesaprob += creditos;
        }
        cout << endl;
    }
}

void imprimirCursoAlumno(int contador, char* codigo, double creditos, int nota,
        int dia, int mes, int anho) {
    // Imprimir el número de cursos
    cout << right << setfill('0') << setw(3) << contador << setfill(' ');
    // Imprimir líneas extra si el curso es desaprobatorio
    if (nota < MIN_APROBADA) {
        cout << setw(40) << ' ';
    }
    // Imprimir el código y número de créditos del curso
    cout << fixed << setprecision(2);
    cout << setw(8) << codigo << "  " << setw(8) << creditos << "  ";
    // Imprimir la nota del curso
    cout << right << setfill('0') << setw(2) << nota << setfill(' ') << "  ";
    // Imprimir la fecha del curso
    cout << setw(5) << anho << '/' << setfill('0') << setw(2) << mes << '/';
    cout << setw(2) << dia << setfill(' ');
    // Imprimir líneas extra si el curso es aprobatorio
    if (nota >= MIN_APROBADA) {
        cout << setw(40) << ' ';
    }
}

void imprimirResumenAlumno(int numCursos, double credAprob, double credDesaprob,
        int numCurAprob, int numCurError, double sumaNotas, double sumaAprob) {
    separacion('=');
    cout << "RESUMEN:" << endl;
    // Imprimir cursos matriculados y total de créditos
    cout << left << setw(8) << ' ' << "Cursos matriculados:" << right << setw(9) << numCursos << setw(10) << ' ';
    cout << left << "Total de creditos:" << right << setw(14) << (credAprob+credDesaprob) << endl;
    // Imprimir créditos aprobados y desaprobados
    cout << left << setw(8) << ' ' << "Creditos aprobados:" << right << setw(10) << credAprob << setw(10) << ' ';
    cout << left << "Creditos desaprobados:" << right << setw(10) << credDesaprob << endl;
    // Imprimir porcentaje de créditos aprobados
    cout << left << setw(8) << ' ' << "Creditos aprobados/matriculados: ";
    cout << right << (credAprob*100/(credAprob+credDesaprob)) << '%' << endl;
    separacion('-');
    // Imprimir promedios
    cout << left << setw(8) << ' ' << "Promedio general: " << right << setw(21) << (sumaNotas/numCursos) << endl;
    cout << left << setw(8) << ' ' << "Promedio general de aprobados: " << right << setw(8) << (sumaAprob/numCurAprob) << endl;
    separacion('-');
    // Imprimir cursos con error
    cout << "Cursos con error no considerados: " << setfill('0') << setw(2) << numCurError << setfill(' ') << endl;
    separacion('=');
}

void separacion(char caracter) {
    for (int i = 0; i < MAX_LINEA; i++) {
        cout << caracter;
    }
    cout << endl;
}
