/*
 * Archivo: MuyGrave.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#ifndef MUYGRAVE_H
#define MUYGRAVE_H

#include "Infraccion.h"
#include "Falta.h"

class MuyGrave : public Infraccion, public Falta {
public:
    MuyGrave();
    virtual ~MuyGrave();
    // Encapsulamiento
    int GetMeses() const;
    void SetMeses(int meses);
    int GetPuntos() const;
    void SetPuntos(int puntos);
private:
    int puntos;
    int meses;
};

#endif /* MUYGRAVE_H */
