/*
 * Archivo: Urgencia.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef URGENCIA_H
#define URGENCIA_H

#include "Paciente.h"

class Urgencia : public Paciente {
public:
    Urgencia();
    Urgencia(const Urgencia& orig);
    virtual ~Urgencia();
    // Métodos
    int orden();
    bool seguro();
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    // Encapsulamiento
    double getPorcSeguro() const;
    void setPorcSeguro(double);
    double getPorcUrgencia() const;
    void setPorcUrgencia(double);
private:
    double porcSeguro;
    double porcUrgencia;
};

#endif /* URGENCIA_H */
