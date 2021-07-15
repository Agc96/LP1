/*
 * Archivo: Grave.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#ifndef GRAVE_H
#define GRAVE_H

#include "Infraccion.h"
#include "Falta.h"

class Grave : public Infraccion, public Falta {
public:
    Grave();
    virtual ~Grave();
    // Encapsulamiento
    double GetDescuento() const;
    void SetDescuento(double descuento);
    int GetPuntos() const;
    void SetPuntos(int puntos);
private:
    double descuento;
    int puntos;
};

#endif /* GRAVE_H */

