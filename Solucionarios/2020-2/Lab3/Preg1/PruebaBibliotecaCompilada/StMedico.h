/*
 * Archivo: StMedico.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de octubre de 2020, 08:45 AM
 */

#ifndef STMEDICO_H
#define STMEDICO_H

#define STMEDICO_MAX_CODIGO 10
#define STMEDICO_MAX_NOMBRE 50
#define STMEDICO_MAX_ESPECIALIDAD 20
#define STMEDICO_MAX_PACIENTES 100

struct StMedico {
    char codigo[STMEDICO_MAX_CODIGO];
    char nombre[STMEDICO_MAX_NOMBRE];
    char especialidad[STMEDICO_MAX_ESPECIALIDAD];
    double tarifa;
    int fechas[STMEDICO_MAX_PACIENTES];
    int pacientes[STMEDICO_MAX_PACIENTES];
    double prima[STMEDICO_MAX_PACIENTES];
    char estado[STMEDICO_MAX_PACIENTES];
    int numPac = 0;
    double ingresosP = 0.0;
    double ingresosS = 0.0;
};

#endif /* STMEDICO_H */
