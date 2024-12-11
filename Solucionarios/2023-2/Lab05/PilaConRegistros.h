/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PilaConRegistros.h
 * Author: cueva
 *
 * Created on 22 de octubre de 2022, 10:53 PM
 */
#include <fstream>
using namespace std;

#ifndef PILACONREGISTROS_H
#define PILACONREGISTROS_H

void* leeregistro(ifstream &);
int cmpregistro(const void*,const void*);
void imprimeregistro(ofstream &,void* );
double calcularegistro(void *);
    
#endif /* PILACONREGISTROS_H */
