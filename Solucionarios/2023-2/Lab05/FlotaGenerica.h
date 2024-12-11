
/* 
 * File:   FlotaGenerica.h
 * Author: cueva
 *
 * Created on 23 de septiembre de 2023, 21:46
 */
#include <fstream>
using namespace std;

#ifndef FLOTAGENERICA_H
#define FLOTAGENERICA_H
    void generapila(void*&);
    void push(void *&,void*,double);
    void cargacamiones(void *&,int ,double ,
        void*(*)(ifstream&),double(*)(void*), const char*);
    void  muestracamiones(void *,int n,void(*)(ofstream&,void*),const char*);
#endif /* FLOTAGENERICA_H */
