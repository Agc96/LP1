/*
 * Archivo: Leve.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#ifndef LEVE_H
#define LEVE_H

#include "Infraccion.h"
#include "Falta.h"

class Leve : public Infraccion, public Falta {
public:
    Leve();
    virtual ~Leve();
    // Encapsulamiento
    double GetDescuento() const;
    void SetDescuento(double descuento);
private:
    double descuento;
};

#endif /* LEVE_H */

