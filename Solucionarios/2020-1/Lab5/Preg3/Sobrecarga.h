/* 
 * Archivo: Sobrecarga.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef SOBRECARGA_H
#define SOBRECARGA_H

#include <iostream>
#include "Aula.h"
using namespace std;

istream& operator >>(istream&, class Aula&);
ostream& operator <<(ostream&, class Aula&);

#endif /* SOBRECARGA_H */
