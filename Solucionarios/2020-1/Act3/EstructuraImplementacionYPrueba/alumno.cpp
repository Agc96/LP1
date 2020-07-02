/* 
 * Archivo: alumno.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 15 de mayo de 2020, 08:29 AM
 */

#include "alumno.h"

void operator +(const Alumno& alumno, const ACurso& aCurso) {
    // TODO
}

void operator *(const Alumno&, const ACurso&) {
    // TODO
}

void operator -(const Alumno&, const ACurso&) {
    // TODO
}

double operator /(const Alumno& alumno, int ciclo) {
    int sumaNotas = 0;
    for (int i = 0; i < alumno.numcur; i++) {
        sumaNotas += alumno.nota[i];
    }
    return sumaNotas > 0 ? (double)sumaNotas/alumno.numcur : 0;
}

double operator --(const Alumno& alumno) {
    double credCursados = 0;
    for (int i = 0; i < alumno.numcur; i++) {
        credCursados += alumno.credito[i];
    }
    return credCursados;
}

double operator ++(const Alumno& alumno) {
    double credAprobados = 0;
    for (int i = 0; i < alumno.numcur; i++) {
        if (alumno.nota[i] > 10) {
            credAprobados += alumno.credito[i];
        }
    }
    return credAprobados;
}

istream& operator >>(istream& in, const Alumno& alumno) {
    char especialidad[MAX_CADENA], facultad[MAX_CADENA];
    int carne;
    // Leer los datos principales
    in >> alumno.tipo >> alumno.codigo >> alumno.nombre;
    // Ignorar el resto de datos
    in >> carne;
    if (in.fail()) in.clear();
    in >> especialidad >> facultad;
    return in;
}

istream& operator >>(istream& in, const ACurso& acurso) {
    int anho, periodo;
    char c;
    // Leer los datos principales
    in >> acurso.codigo >> acurso.curso >> acurso.nota;
    // Leer el ciclo del curso
    in >> anho >> c >> periodo;
    acurso.ciclo = anho * 10000 + periodo;
    // Leer el resto de datos
    in >> acurso.credito >> acurso.operacion;
    return in;
}

ostream& operator <<(ostream& out, const Alumno& alumno) {
    // Imprimir datos principales
    out << "Nombre: " << alumno.nombre << endl;
    out << "Codigo: " << alumno.codigo << endl;
    separador(out);
    // Imprimir lista de ciclos
    out << setw(5) << ' ' << setw(10) << "CICLO" << setw(20) << "PROMEDIO" << endl;
    for (int i = 0; i < alumno.numcur; i++) {
        // out << setw(3) << 0 << ") " << setw(10) << /* TODO << */ endl;
    }
    // Imprimir estadísticas
    out << "Creditos Cursados: " << --alumno;
    out << "Creditos Aprobados: " << ++alumno;
    separador(out);
    return out;
}

void separador(ostream& out) {
    for (int i = 0; i < MAX_LINEA; i++) {
        out << '=';
    }
    out << endl;
}
