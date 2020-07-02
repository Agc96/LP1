/* 
 * Archivo: Curso.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef CURSO_H
#define CURSO_H

class Curso {
public:
    Curso();
    Curso(const Curso& orig);
    virtual ~Curso();
    /* Asignación */
    const Curso& asignar(const Curso&);
    const Curso& operator =(const Curso&);
    /* Comparación */
    bool compare(const Curso&);
    bool operator ==(const Curso&);
    /* Encapsulamiento */
    char* GetCcurso() const;
    void SetCcurso(char*);
    int GetCiclo() const;
    void SetCiclo(int);
    double GetCredito() const;
    void SetCredito(double);
    int GetNota() const;
    void SetNota(int);
private:
    char* ccurso;
    int ciclo;
    int nota;
    double credito;
};

#endif /* CURSO_H */

