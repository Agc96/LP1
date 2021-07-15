/*
 * Archivo: Infraccion.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:51 AM
 */

#ifndef INFRACCION_H
#define INFRACCION_H

class Infraccion {
public:
    Infraccion(); // No es necesario usar un constructor copia
    virtual ~Infraccion();
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    char* GetGravedad() const;
    void SetGravedad(const char* gravedad);
    double GetMulta() const;
    void SetMulta(double multa);
private:
    int codigo;
    char* gravedad;
    double multa;
};

#endif /* INFRACCION_H */

