/* 
 * Archivo: Alumno.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Curso.h"
#include "ACurso.h"

#define MAX_CURSO 50

class Alumno {
public:
    Alumno();
    Alumno(const Alumno& orig);
    virtual ~Alumno();
    /* Operadores */
    void operator +(const ACurso&);
    void operator *(const ACurso&);
    void operator -(const ACurso&);
    double operator /(int);
    double operator ++();
    double operator --();
    /* Encapsulamiento */
    int GetCodigo() const;
    void SetCodigo(int);
    char GetTipo() const;
    void SetTipo(char);
    char* GetNombre() const;
    void SetNombre(char*);
    Curso GetLcursoAt(int) const;
    void SetLcursoAt(int, const Curso&);
    int GetNumcur() const;
    void SetNumcur(int);
private:
    int codigo;
    char tipo;
    char* nombre;
    Curso lcurso[MAX_CURSO];
    int numcur;
};

#endif /* ALUMNO_H */
