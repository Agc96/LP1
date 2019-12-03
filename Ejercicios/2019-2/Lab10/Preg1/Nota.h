/* 
 * Archivo: Nota.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:26 AM
 */

#ifndef NOTA_H
#define NOTA_H

class Nota {
public:
    Nota();
    Nota(const Nota&);
    virtual ~Nota();
    // Getters y setters
    char* getCodigo();
    void setCodigo(char*);
    char* getSemestre();
    void setSemestre(char*);
    int getNota();
    void setNota(int);
private:
    char* codigo;
    int nota;
    char* semestre;
    char* copia(char*);
};

#endif /* NOTA_H */

