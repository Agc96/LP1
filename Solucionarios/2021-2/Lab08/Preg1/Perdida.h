/*
 * File:   Perdida.h
 * Author: Anthony Gutiérrez
 *
 * Created on 23 de noviembre de 2021, 12:07 AM
 */

#ifndef PERDIDA_H
#define PERDIDA_H

class Perdida {
public:
    Perdida();
    Perdida(const Perdida& orig);
    virtual ~Perdida();
    // Encapsulamiento
    double GetPrecio() const;
    void SetPrecio(double precio);
private:
    double precio;
};

#endif /* PERDIDA_H */
