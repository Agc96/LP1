/*
 * File:   NLibro.h
 * Author: Anthony Gutiérrez
 *
 * Created on 3 de diciembre de 2021, 08:16 AM
 */

#ifndef NLIBRO_H
#define NLIBRO_H

#include "Libro.h"

class NLibro {
public:
    NLibro();
    NLibro(const NLibro& orig);
    virtual ~NLibro();
    friend class ALibro;
private:
    Libro dlibro;
    NLibro* izq;
    NLibro* der;
};

#endif /* NLIBRO_H */

