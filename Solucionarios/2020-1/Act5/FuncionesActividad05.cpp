/*
 * Archivo: FuncionesActividad05.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iomanip>
#include <cstring>
#include "FuncionesActividad05.h"

#define MAX_LINEA 120
#define MAX_NOMBRE 50
#define MAX_REGISTROS 50
#define MAX_CODIGO 10
#define MIN_APROBATORIO 10.5
#define CABECERA 15

enum Posicion {CODIGO, NOMBRE, CRED_CURSADOS, CRED_APROBADOS, NUM_CURSOS,
               SUMA_NOTAS, ARR_CURSOS};

void leerAlumnos(void *&alumnos) {
    ifstream arch("Alumnos.csv", ios::in);
    validarArchivo(arch, "Alumnos.csv");
    // Declaración de variables
    void *buffer[MAX_REGISTROS], **alumnosAux, *registro;
    int numAlumnos = 0;
    // Iterar y leer los datos de cada alumno
    while (true) {
        registro = crearRegistro(arch);
        if (registro == nullptr) break;
        buffer[numAlumnos++] = registro;
    }
    // Copiar los datos del alumno en un nuevo arreglo
    alumnosAux = new void*[numAlumnos + 1];
    for (int i = 0; i < numAlumnos; i++) {
        alumnosAux[i] = buffer[i];
    }
    alumnosAux[numAlumnos] = nullptr;
    alumnos = alumnosAux;
}

void* crearRegistro(ifstream& arch) {
    char c, nombre[MAX_NOMBRE];
    int codigo;
    // Leer el código del alumno
    arch >> c >> c >> codigo >> c;
    if (arch.eof()) return nullptr;
    // Leer el nombre del alumno
    arch.getline(nombre, MAX_NOMBRE, ',');
    while (arch.get() != '\n');
    // Guardar los datos
    void** registro = new void*[7];
    registro[CODIGO] = crearEntero(codigo);
    registro[NOMBRE] = crearCadena(nombre);
    registro[CRED_CURSADOS] = crearReal(0.0);
    registro[CRED_APROBADOS] = crearReal(0.0);
    registro[NUM_CURSOS] = crearEntero(0);
    registro[SUMA_NOTAS] = crearEntero(0);
    registro[ARR_CURSOS] = nullptr;
    return registro;
}

void imprimirAlumnos(void *alumnos) {
    ofstream reporte("Alumnos.txt", ios::out);
    validarArchivo(reporte, "Alumnos.txt");
    // Declaración de variables
    void ***alumnosAux = (void***)alumnos;
    double *credCurs, *credAprob;
    int *codigo, *numCursos, *sumaNotas;
    char *nombre;
    // Imprimir cabecera
    reporte << left << setw(MAX_CODIGO) << "CODIGO" << setw(MAX_NOMBRE) << "NOMBRE"
            << setw(CABECERA) << "CRED. CURS." << setw(CABECERA) << "CRED. AP."
            << setw(CABECERA) << "NUM. CURS." << setw(CABECERA) << "SUMA NOTAS"
            << endl;
    separacion(reporte);
    // Obtener los datos de cada alumno
    reporte << fixed << setprecision(2);
    for (int i = 0; alumnosAux[i] != nullptr; i++) {
        codigo = (int*)(alumnosAux[i][CODIGO]);
        nombre = (char*)(alumnosAux[i][NOMBRE]);
        credCurs = (double*)(alumnosAux[i][CRED_CURSADOS]);
        credAprob = (double*)(alumnosAux[i][CRED_APROBADOS]);
        numCursos = (int*)(alumnosAux[i][NUM_CURSOS]);
        sumaNotas = (int*)(alumnosAux[i][SUMA_NOTAS]);
        // Imprimir datos en el archivo
        reporte << left << setw(MAX_CODIGO) << *codigo << setw(MAX_NOMBRE) << nombre
                << right << setw(CABECERA) << *credCurs << setw(CABECERA) << *credAprob
                << setw(CABECERA) << *numCursos << setw(CABECERA) << *sumaNotas
                << endl;
    }
}

void leerCursos(void *alumnos) {
    ifstream arch("Cursos.csv", ios::in);
    validarArchivo(arch, "Cursos.csv");
    // Declaración de variables
    void ***alumnosAux = (void***)alumnos;
    int codAlumnoBuscado, *codAlumnoLeido, nota, ciclo;
    char codCurso[MAX_CODIGO], c;
    double creditos;
    // Iterar y leer los datos de cada curso-alumno
    while (true) {
        arch >> codAlumnoBuscado >> c;
        if (arch.eof()) break;
        arch.getline(codCurso, MAX_CODIGO, ',');
        arch >> nota >> c >> ciclo >> c >> ciclo >> c >> creditos >> c >> c;
        // Actualizar los datos
        for (int i = 0; alumnosAux[i] != nullptr; i++) {
            codAlumnoLeido = (int*)(alumnosAux[i][CODIGO]);
            if ((*codAlumnoLeido) == codAlumnoBuscado) {
                actualizarAlumno(alumnosAux[i], codCurso, nota, creditos);
                break;
            }
        }
    }
}

void actualizarAlumno(void **alumno, char *curso, int nota, double creditos) {
    // Obtener datos a actualizar
    double *credCursados = (double*)(alumno[CRED_CURSADOS]);
    double *credAprobados = (double*)(alumno[CRED_APROBADOS]);
    int *numCursos = (int*)(alumno[NUM_CURSOS]);
    int *sumaNotas = (int*)(alumno[SUMA_NOTAS]);
    // Actualizar datos
    (*credCursados) += creditos;
    (*numCursos)++;
    (*sumaNotas) += nota;
    if (nota > MIN_APROBATORIO) {
        (*credAprobados) += creditos;
        // Actualizar arreglo de cursos
        char *cursoAux = crearCadena(curso);
        void **arrCursos = (void**)(alumno[ARR_CURSOS]);
        alumno[ARR_CURSOS] = agregarConIncremento(arrCursos, cursoAux);
    }
}

void* agregarConIncremento(void **arreglo, void *registro) {
    int numReg = 0;
    if (arreglo != nullptr) {
        // Calcular el número de registros
        for (numReg = 0; arreglo[numReg] != nullptr; numReg++);
        // Copiar los datos en un nuevo arreglo
        void** nuevoArr = new void*[numReg + 2];
        for (int i = 0; i < numReg; i++) {
            nuevoArr[i] = arreglo[i];
        }
        // Reemplazar el arreglo anterior con el nuevo
        delete arreglo;
        arreglo = nuevoArr;
    } else {
        // Crear el arreglo de alumnos para el primer caso
        arreglo = new void*[2];
    }
    // Agregar los datos del registro
    arreglo[numReg] = registro;
    arreglo[numReg + 1] = nullptr;
    return arreglo;
}

void consolidado(void *alumnos) {
    ofstream reporte("Consolidado.txt", ios::out);
    validarArchivo(reporte, "Consolidado.txt");
    // Declaración de variables
    void ***alumnosAux = (void***)alumnos;
    // Obtener los datos de cada alumno
    reporte << left << fixed << setprecision(2);
    for (int i = 0; alumnosAux[i] != nullptr; i++) {
        // Imprimir los datos del alumnno y curso
        imprimirAlumno(reporte, alumnosAux[i]);
        if (alumnosAux[i][ARR_CURSOS] != nullptr) {
            imprimirCursos(reporte, alumnosAux[i][ARR_CURSOS]);
        }
        reporte << endl;
        // Borrar el registro
        delete alumnosAux[i];
    }
    // Borrar la lista de alumnos
    delete alumnosAux;
}

void imprimirAlumno(ofstream& reporte, void **alumno) {
    // Castear los datos del alumno
    int *codigo = (int*)(alumno[CODIGO]);
    char *nombre = (char*)(alumno[NOMBRE]);
    double *credCursados = (double*)(alumno[CRED_CURSADOS]);
    double *credAprobados = (double*)(alumno[CRED_APROBADOS]);
    int *numCursos = (int*)(alumno[NUM_CURSOS]);
    int *sumaNotas = (int*)(alumno[SUMA_NOTAS]);
    // Calcular el promedio y mostrar los datos del alumno
    double promedio = (*numCursos > 0) ? (double)(*sumaNotas) / *numCursos : 0;
    reporte << "Código: " << setw(MAX_CODIGO) << *codigo
            << "Nombre: " << setw(MAX_NOMBRE) << nombre
            << "Cred.: " << setw(MAX_CODIGO) << *credCursados
            << "Cred. Apro.: " << setw(MAX_CODIGO) << *credAprobados
            << "Prom. Gene.: " << setw(MAX_CODIGO) << promedio << endl;
    // Borrar los datos del alumno
    delete codigo, numCursos, sumaNotas;
    delete nombre;
    delete credCursados, credAprobados;
}

void imprimirCursos(ofstream& reporte, void *cursos) {
    void **cursosAux = (void**)cursos;
    char *curso;
    // Imprimir cabecera
    reporte << "Cursos aprobados:";
    // Recorrer la lista de cursos
    for (int i = 0; cursosAux[i] != nullptr; i++) {
        // Imprimir el curso
        curso = (char*)(cursosAux[i]);
        reporte << ' ' << curso;
        // Borrar el curso
        delete curso;
    }
    reporte << endl;
    delete cursosAux;
}

/* Funciones auxiliares */

void validarArchivo(ios& arch, const char* nomArch) {
    if (!arch) {
        cerr << "No se pudo abrir o crear el archivo " << nomArch << endl;
        exit(1);
    }
}

int* crearEntero(int entero) {
    int* nuevoEntero = new int;
    *nuevoEntero = entero;
    return nuevoEntero;
}

double* crearReal(double real) {
    double* nuevoReal = new double;
    *nuevoReal = real;
    return nuevoReal;
}

char* crearCadena(char* cadena) {
    int tamanho = strlen(cadena);
    char* nuevaCadena = new char[tamanho + 1];
    strcpy(nuevaCadena, cadena);
    return nuevaCadena;
}

void separacion(ostream& arch) {
    for (int i = 0; i < MAX_LINEA; i++) {
        arch << '=';
    }
    arch << endl;
}
