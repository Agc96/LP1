/*
 * Archivo: LFalta.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:08 AM
 */

#ifndef LFALTA_H
#define LFALTA_H

#include "Infraccion.h"
#include "Falta.h"
#include "NFalta.h"

class LFalta {
public:
    LFalta();
    virtual ~LFalta();
    // Métodos
    void leer(const char* nomArch);
    void unir(const LFalta& lfalta);
    void imprimir(const char* nomArch);
private:
    class NFalta* lini;
    class NFalta* lfin;
    // Métodos auxiliares
    class Infraccion* leerInfraccion(int infraccion);
    void agregarFalta(class Infraccion* pfalta, Falta* dfalta);
};

#endif /* LFALTA_H */
