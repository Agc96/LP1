/*
 * File:   Prestamo.h
 * Author: Anthony Gutiérrez
 *
 * Created on 23 de noviembre de 2021, 12:07 AM
 */

#ifndef PRESTAMO_H
#define PRESTAMO_H

class Prestamo {
public:
    Prestamo();
    Prestamo(const Prestamo& orig);
    virtual ~Prestamo();
    // Encapsulamiento
    int GetDias() const;
    void SetDias(int dias);
    int GetFecha() const;
    void SetFecha(int fecha);
private:
    int dias;
    int fecha;
};

#endif /* PRESTAMO_H */
