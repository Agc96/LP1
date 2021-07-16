/*
 * Archivo: NFalta.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:08 AM
 */

#ifndef NFALTA_H
#define NFALTA_H

#include "Infraccion.h"
#include "Falta.h"
#include "LFalta.h"

class NFalta {
public:
    NFalta();
    virtual ~NFalta();
private:
    class Infraccion* pfalta;
    class Falta* dfalta;
    class NFalta* sig;
    friend class LFalta;
};

#endif /* NFALTA_H */
