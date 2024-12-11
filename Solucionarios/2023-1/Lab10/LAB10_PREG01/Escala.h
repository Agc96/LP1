/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:19 AM
 */

#ifndef ESCALA_H
#define ESCALA_H

class Escala {
public:
    Escala();
    Escala(const Escala& orig);
    virtual ~Escala();
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    double GetPrecio() const;
    void SetPrecio(double precio);
private:
    int codigo;
    double precio;
};

#endif /* ESCALA_H */
