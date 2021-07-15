/*
 * Archivo: Falta.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:50 AM
 */

#ifndef FALTA_H
#define FALTA_H

class Falta {
public:
    Falta();
    Falta(const Falta& orig);
    virtual ~Falta();
    // Encapsulamiento
    int GetFecha() const;
    void SetFecha(int fecha);
    char* GetPlaca() const;
    void SetPlaca(const char* placa);
private:
    int fecha;
    char* placa;
};

#endif /* FALTA_H */
