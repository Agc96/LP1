/*
 * Archivo: Ambulatorio.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef AMBULATORIO_H
#define AMBULATORIO_H

#include "Paciente.h"

class Ambulatorio : public Paciente {
public:
    Ambulatorio();
    Ambulatorio(const Ambulatorio& orig);
    virtual ~Ambulatorio();
    // Métodos
    int orden();
    bool seguro();
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    // Encapsulamiento
    double getPorcSeguro() const;
    void setPorcSeguro(double);
private:
    double porcSeguro;
};

#endif /* AMBULATORIO_H */
