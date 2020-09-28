/* 
 * Archivo: Persona.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef PERSONA_H
#define PERSONA_H

class Persona {
public:
    Persona();
    Persona(const Persona& orig);
    virtual ~Persona();
    /* Encapsulamiento */
    int GetCodigo() const;
    void SetCodigo(int codigo);
    void GetDistrito(char*) const;
    void SetDistrito(char*);
    void GetNombre(char*) const;
    void SetNombre(char*);
private:
    char* nombre;
    int codigo;
    char* distrito;
    void inicializar();
};

#endif /* PERSONA_H */

