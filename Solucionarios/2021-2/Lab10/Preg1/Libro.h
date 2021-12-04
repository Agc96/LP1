/*
 * File:   Libro.h
 * Author: Anthony Gutiérrez
 *
 * Created on 3 de diciembre de 2021, 08:13 AM
 */

#ifndef LIBRO_H
#define LIBRO_H

class Libro {
public:
    Libro();
    Libro(const Libro& orig);
    virtual ~Libro();
    // Encapsulamiento
    int GetAnho() const;
    void SetAnho(int anho);
    void GetAutor(char* autor) const;
    void SetAutor(const char* autor);
    int GetCantidad() const;
    void SetCantidad(int cantidad);
    void GetCodigo(char* codigo) const;
    void SetCodigo(const char* codigo);
    double GetPrecio() const;
    void SetPrecio(double precio);
    int GetStock() const;
    void SetStock(int stock);
    void GetTitulo(char* titulo) const;
    void SetTitulo(const char* titulo);
private:
    char* codigo;
    char* titulo;
    char* autor;
    int cantidad;
    int stock;
    int anho;
    double precio;
};

#endif /* LIBRO_H */
