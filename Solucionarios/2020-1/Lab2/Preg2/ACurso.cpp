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
    this->codigo = orig.codigo;
    this->operacion = orig.operacion;
    this->curso = orig.curso;
}

ACurso::~ACurso() {
    // C++ invoca al destructor de this->curso.
}

/* Encapsulamiento */

int ACurso::GetCodigo() const {
    return codigo;
}

void ACurso::SetCodigo(int codigo) {
    this->codigo = codigo;
}

Curso ACurso::GetCurso() const {
    return curso;
}

void ACurso::SetCurso(const Curso& curso) {
    this->curso = curso;
}

char ACurso::GetOperacion() const {
    return operacion;
}

void ACurso::SetOperacion(char operacion) {
    this->operacion = operacion;
}
