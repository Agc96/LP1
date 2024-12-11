/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: ConReceta.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#ifndef CONRECETA_H
#define CONRECETA_H

#include "Medicamento.h"

class ConReceta : public Medicamento {
public:
    ConReceta();
    ConReceta(const ConReceta& orig);
    virtual ~ConReceta();
    // Encapsulamiento
    int GetCodmed() const;
    void SetCodmed(int codmed);
    void GetEspecialidad(char* especialidad) const;
    void SetEspecialidad(const char* especialidad);
private:
    int codmed;
    char *especialidad;
};

#endif /* CONRECETA_H */
