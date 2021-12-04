/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Biblioteca.h
 * Author: Anthony
 *
 * Created on 3 de diciembre de 2021, 08:16 AM
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "ALibro.h"

class Biblioteca {
public:
    Biblioteca();
    Biblioteca(const Biblioteca& orig);
    virtual ~Biblioteca();
private:
    ALibro AStock;
};

#endif /* BIBLIOTECA_H */

