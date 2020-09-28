/* 
 * Archivo: Persona.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
using namespace std;

class Persona {
public:
    Persona();
    Persona(const Persona&);
    virtual ~Persona();
    /* Operadores sobrecargados */
    Persona& operator =(const Persona&);
    /* Lectura e impresión de datos */
    virtual istream& leer(istream&);
    virtual ostream& imprimir(ostream&);
    /* Encapsulamiento */
    int GetCodigo() const;
    void SetCodigo(int);
    char* GetDistrito() const;
    void SetDistrito(char*);
    char* GetNombre() const;
    void SetNombre(char*);
private:
    char* nombre;
    int codigo;
    char* distrito;
    virtual void inicializar();
protected:
    char* crearCadena(char*) const;
    const int MAX_LINEA = 120;
};

#endif /* PERSONA_H */
