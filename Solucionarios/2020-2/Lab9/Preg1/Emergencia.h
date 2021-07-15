/*
 * Archivo: Emergencia.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef EMERGENCIA_H
#define EMERGENCIA_H

#include "Paciente.h"

class Emergencia : public Paciente {
public:
    Emergencia();
    Emergencia(const Emergencia& orig);
    virtual ~Emergencia();
    // Métodos
    int orden();
    bool seguro();
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    // Encapsulamiento
    char* getNombreRef() const;
    void setNombreRef(char*);
    int getTelefonoRef() const;
    void setTelefonoRef(int);
private:
    int telefonoRef;
    char *nombreRef;
};

#endif /* EMERGENCIA_H */
