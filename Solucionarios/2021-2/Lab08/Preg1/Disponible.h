/*
 * File:   Disponible.h
 * Author: Anthony Gutiérrez
 *
 * Created on 23 de noviembre de 2021, 12:06 AM
 */

#ifndef DISPONIBLE_H
#define DISPONIBLE_H

class Disponible {
public:
    Disponible();
    Disponible(const Disponible& orig);
    virtual ~Disponible();
    // Encapsulamiento
    int GetZona() const;
    void SetZona(int zona);
private:
    int zona;
};

#endif /* DISPONIBLE_H */
