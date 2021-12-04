/*
 * File:   ALibro.h
 * Author: Anthony Gutiérrez
 *
 * Created on 3 de diciembre de 2021, 08:16 AM
 */

#ifndef ALIBRO_H
#define ALIBRO_H

#include "NLibro.h"

class ALibro {
public:
    ALibro();
    ALibro(const ALibro& orig);
    virtual ~ALibro();
private:
    NLibro* Raiz;
};

#endif /* ALIBRO_H */

