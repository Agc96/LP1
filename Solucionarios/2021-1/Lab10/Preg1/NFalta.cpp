/*
 * Archivo: NFalta.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:08 AM
 */

#include "NFalta.h"

NFalta::NFalta() {
    pfalta = nullptr;
    dfalta = nullptr;
    sig = nullptr;
}

NFalta::~NFalta() {
    if (pfalta) delete pfalta;
    if (dfalta) delete dfalta;
    // La eliminación de sig será realizada en LFalta.
}
