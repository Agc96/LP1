/*
 * Archivo: AlumnoNota.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:15 AM
 */

#ifndef ALUMNONOTA_H
#define ALUMNONOTA_H

#include <iostream>
#include <fstream>
#include "Nota.h"
using namespace std;

class AlumnoNota {
public:
    AlumnoNota();
    AlumnoNota(const AlumnoNota& orig);
    virtual ~AlumnoNota();
    // Encapsulamiento
    int GetCiclo() const;
    void SetCiclo(int ciclo);
    void GetCodCurso(char *cadena) const;
    void SetCodCurso(const char *cadena);
    int GetCodigo() const;
    void SetCodigo(int codigo);
    int GetNota() const;
    void SetNota(int nota);
    // Sobrecarga de totalización
    void operator &(Nota &nota);
private:
    int codigo;
    char *codcurso;
    int ciclo;
    int nota;
};

// Sobrecarga de lectura
ifstream& operator >>(ifstream &arch, AlumnoNota &alumnoNota);

#endif /* ALUMNONOTA_H */
