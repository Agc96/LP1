/*
 * Archivo: Alumno.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:16 AM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <fstream>
#include "Constantes.h"
#include "Nota.h"
using namespace std;

class Alumno {
public:
    Alumno();
    Alumno(const Alumno& orig);
    virtual ~Alumno();
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    void GetNombre(char *cadena) const;
    void SetNombre(const char *cadena);
    int GetNumAprobados() const;
    void SetNumAprobados(int numaprobados);
    int GetNumCursos() const;
    void SetNumCursos(int numcursos);
    int GetNumPrimera() const;
    void SetNumPrimera(int numprimera);
    int GetNumSegunda() const;
    void SetNumSegunda(int numsegunda);
    int GetNumTercera() const;
    void SetNumTercera(int numtercera);
    // Sobrecarga de agregación
    void operator +=(Nota &nota);
private:
    int codigo;
    char *nombre;
    int numcursos;
    int numaprobados;
    int numprimera;
    int numsegunda;
    int numtercera;
    Nota lnotas[MAX_NOTAS];
};

// Sobrecargas de lectura e impresión
ifstream& operator >>(ifstream &arch, Alumno &alumno);
ofstream& operator <<(ofstream &arch, Alumno &alumno);

#endif /* ALUMNO_H */
