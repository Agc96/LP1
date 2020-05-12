/* 
 * Archivo: utilidades.h
 * Autor:   Anthony Gutiérrez <anthony.gutierrez@pucp.pe>
 * Código:  20130095
 *
 * Created on 13 de septiembre de 2019, 08:43 PM
 */

#include <fstream>
using namespace std;

#ifndef UTILIDADES_H
#define UTILIDADES_H

void separacion(ofstream&, char, int);
void espacios(ofstream&, int);
void repetir(ofstream&, char, int, bool);
double obtenerTipoCambio(ifstream&, char);

#endif /* UTILIDADES_H */
