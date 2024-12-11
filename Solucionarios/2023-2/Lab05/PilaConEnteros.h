/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PilaConEnteros.h
 * Author: cueva
 *
 * Created on 22 de octubre de 2022, 07:28 AM
 */
#include <fstream>

using namespace std;

#ifndef PILACONENTEROS_H
#define PILACONENTEROS_H

void* leenumero(ifstream &);
int cmpnumero(const void*,const void*);
void imprimenumero(ofstream &,void*);
double calculanumero(void *);

#endif /* PILACONENTEROS_H */
