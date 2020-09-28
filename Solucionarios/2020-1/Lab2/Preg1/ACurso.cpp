/* 
 * Archivo: ACurso.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "ACurso.h"

ACurso::ACurso() {
    this->codigo = 0;
    this->operacion = '\0';
}

ACurso::ACurso(const ACurso& orig) {
    SetCodigo(orig.codigo);
    SetCurso(orig.clcurso);
    SetOperacion(orig.operacion);
}

ACurso::~ACurso() {
    // C++ invoca al destructor de this->clcurso.
}

/* Encapsulamiento */

int ACurso::GetCodigo() const {
    return codigo;
}

void ACurso::SetCodigo(int codigo) {
    this->codigo = codigo;
}

Curso ACurso::GetCurso() const {
    return clcurso;
}

void ACurso::SetCurso(const Curso& clcurso) {
    this->clcurso = clcurso;
}

char ACurso::GetOperacion() const {
    return operacion;
}

void ACurso::SetOperacion(char operacion) {
    this->operacion = operacion;
}
