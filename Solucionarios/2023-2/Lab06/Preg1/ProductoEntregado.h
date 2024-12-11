/*
 * File:   ProductoEntregado.h
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:33 AM
 */

#ifndef PRODUCTOENTREGADO_H
#define PRODUCTOENTREGADO_H

class ProductoEntregado {
public:
    ProductoEntregado();
    ProductoEntregado(const ProductoEntregado& orig);
    virtual ~ProductoEntregado();
    // Encapsulamiento
    void GetCodigo(char* codigo) const;
    void SetCodigo(const char* codigo);
    double GetPrecio() const;
    void SetPrecio(double precio);
private:
    char *codigo;
    double precio;
};

#endif /* PRODUCTOENTREGADO_H */

