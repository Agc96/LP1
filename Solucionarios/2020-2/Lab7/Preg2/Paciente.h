/*
 * Archivo: Paciente.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
using namespace std;

class Paciente {
public:
    Paciente();
    Paciente(const Paciente&);
    virtual ~Paciente();
    // Métodos y sobrecargas de la clase
    istream& leer(istream&);
    Paciente& operator =(const Paciente&);
    // Encapsulamiento
    int getCodigo() const;
    void setCodigo(int codigo);
    char getEstado() const;
    void setEstado(char estado);
    int getFecha() const;
    void setFecha(int fecha);
    char* getNombre();
    void setNombre(char* nombre);
    double getPrima() const;
    void setPrima(double prima);
private:
    int fecha;
    int codigo;
    char* nombre;
    double prima;
    char estado;
    // Métodos auxiliares
    char* crearCadena(char*);
};

// Sobrecarga de lectura
istream& operator >>(istream&, Paciente&);

#endif /* PACIENTE_H */
