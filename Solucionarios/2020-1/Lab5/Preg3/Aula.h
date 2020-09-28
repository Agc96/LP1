/* 
 * Archivo: Aula.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef AULA_H
#define AULA_H

#include <iostream>
using namespace std;

class Aula {
public:
    Aula();
    Aula(const Aula&);
    virtual ~Aula();
    /* Operadores sobrecargados */
    Aula& operator =(const Aula&);
    /* Sobrecarga de operadores */
    istream& leer(istream&);
    ostream& imprimir(ostream&);
    /* Encapsulamiento */
    int getCapacidad() const;
    void setCapacidad(int);
    char* getClave() const;
    void setClave(char*);
    int getCodigo() const;
    void setCodigo(int);
    char* getNombre() const;
    void setNombre(char*);
    char getTipo() const;
    void setTipo(char);
private:
    char* clave;
    int capacidad;
    int codigo;
    char* nombre;
    char tipo;
    void inicializar();
    char* crearCadena(char*) const;
    const int MAX_LINEA = 120;
};

#endif /* AULA_H */
