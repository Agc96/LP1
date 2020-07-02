/* 
 * Archivo: FuncionesLaboratorio01.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONESLABORATORIO01_H
#define FUNCIONESLABORATORIO01_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void *leeNumero(ifstream &);
void imprimeNumero(ofstream &, void *);
void atiendeNumero(void *&);

#endif /* FUNCIONESLABORATORIO01_H */
