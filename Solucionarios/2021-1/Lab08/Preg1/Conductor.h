/*
 * Archivo: Conductor.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:45 AM
 */

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

class Conductor {
public:
    Conductor(); // No es necesario usar un constructor copia
    virtual ~Conductor();
    // Encapsulamiento
    int GetLicencia() const;
    void SetLicencia(int licencia);
    char* GetNombre() const;
    void SetNombre(const char* nombre);
private:
    int licencia;
    char* nombre;
};

#endif /* CONDUCTOR_H */
