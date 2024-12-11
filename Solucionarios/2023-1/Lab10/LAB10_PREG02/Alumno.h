/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:17 AM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_NOM_ALUMNO 40

class Alumno {
public:
    Alumno();
    Alumno(const Alumno& orig);
    virtual ~Alumno();
    // Encapsulamiento
    int GetCodigo() const;
    void SetCodigo(int codigo);
    double GetCreditos() const;
    void SetCreditos(double creditos);
    int GetEscala() const;
    void SetEscala(int escala);
    void GetNombre(char *cad) const;
    void SetNombre(const char *cad);
    virtual double GetTotal() const;
    virtual void SetTotal(double total);
    // Métodos
    virtual void lee(ifstream &arch);
    virtual void actualizatotal(double precio) = 0;
    virtual void imprime(ofstream &arch);
private:
    int codigo;
    char *nombre;
    int escala;
    double creditos;
    double total;
};

#endif /* ALUMNO_H */
