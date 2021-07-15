/*
 * Archivo: StPaciente.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de octubre de 2020, 08:52 AM
 */

#ifndef STPACIENTE_H
#define STPACIENTE_H

#define STPACIENTE_MAX_NOMBRE 20

struct StPaciente {
    int fecha;
    int codigo;
    char nombre[STPACIENTE_MAX_NOMBRE];
    double prima = 100.0;
    char estado;
};

#endif /* STPACIENTE_H */
