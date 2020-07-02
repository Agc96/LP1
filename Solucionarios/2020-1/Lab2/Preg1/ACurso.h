/* 
 * Archivo: ACurso.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef ACURSO_H
#define ACURSO_H

#include "Curso.h"

class ACurso {
public:
    ACurso();
    ACurso(const ACurso& orig);
    virtual ~ACurso();
    /* Encapsulamiento */
    int GetCodigo() const;
    void SetCodigo(int);
    Curso GetCurso() const;
    void SetCurso(const Curso&);
    char GetOperacion() const;
    void SetOperacion(char);
private:
    int codigo;
    Curso curso;
    char operacion;
};

#endif /* ACURSO_H */

