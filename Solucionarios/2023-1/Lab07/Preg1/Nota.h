/*
 * Archivo: Nota.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:16 AM
 */

#ifndef NOTA_H
#define NOTA_H

class Nota {
public:
    Nota();
    Nota(const Nota& orig);
    virtual ~Nota();
    // Encapsulamiento
    int GetCiclo() const;
    void SetCiclo(int ciclo);
    void GetCodCurso(char *cadena) const;
    void SetCodCurso(const char *cadena);
    int GetNota() const;
    void SetNota(int nota);
private:
    char *codcurso;
    int ciclo;
    int nota;
};

#endif /* NOTA_H */
