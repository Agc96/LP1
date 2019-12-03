/* 
 * Archivo: NumeroMuyGrande.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 12:56 PM
 */

#ifndef NUMEROMUYGRANDE_H
#define NUMEROMUYGRANDE_H

#include <fstream>
using namespace std;

class NumeroMuyGrande {
private:
    // Atributos
    char* digitos;
    int longitud;
    char signo;
    // Métodos auxiliares
    const NumeroMuyGrande& sumar(NumeroMuyGrande&, char);
    const NumeroMuyGrande& restar(NumeroMuyGrande&, char);
    int mayorLongitud(NumeroMuyGrande&);
    void limpiar();
public:
    // Inicialización
    NumeroMuyGrande();
    NumeroMuyGrande(const char*);
    NumeroMuyGrande(NumeroMuyGrande&);
    // Asignación
    void asignar(const char*);
    void asignar(NumeroMuyGrande&);
    void operator =(const char*);
    void operator =(NumeroMuyGrande&);
    // Operaciones
    const NumeroMuyGrande& operator +(NumeroMuyGrande&);
    const NumeroMuyGrande& operator -(NumeroMuyGrande&);
    // Comparación
    int comparar(NumeroMuyGrande&);
    bool operator ==(NumeroMuyGrande&);
    bool operator >(NumeroMuyGrande&);
    bool operator <(NumeroMuyGrande&);
    // Otros métodos
    int length();
    ifstream& leer(ifstream&);
    ofstream& imprimir(ofstream&);
    virtual ~NumeroMuyGrande();
};

#endif /* NUMEROMUYGRANDE_H */
