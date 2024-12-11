/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: SinReceta.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#ifndef SINRECETA_H
#define SINRECETA_H

#include "Medicamento.h"

class SinReceta : public Medicamento {
public:
    SinReceta();
    SinReceta(const SinReceta& orig);
    virtual ~SinReceta();
    // Encapsulamiento
    int GetDni() const;
    void SetDni(int dni);
    void GetNombre(char* nombre) const;
    void SetNombre(const char* nombre);
private:
    int dni;
    char *nombre;
};

#endif /* SINRECETA_H */
