/*
 * File:   LibroPrestado.h
 * Author: Anthony Gutiérrez
 *
 * Created on 12 de noviembre de 2021, 09:17 AM
 */

#ifndef LIBROPRESTADO_H
#define LIBROPRESTADO_H

#include <iostream>
#include <fstream>
using namespace std;

class LibroPrestado {
public:
    LibroPrestado();
    LibroPrestado(const LibroPrestado& orig);
    virtual ~LibroPrestado();
    // Métodos
    ifstream& leer(ifstream& arch);
    ofstream& imprimir(ofstream& arch);
    void calcularDeuda(int fecha);
    // Operadores
    void operator =(const LibroPrestado& orig);
    // Encapsulamiento
    int getCarne() const;
    void setCarne(int carne);
    void getCodigoLib(char *codigoLib) const;
    void setCodigoLib(char *codigoLib);
    int getDeuda() const;
    void setDeuda(int deuda);
    int getFechaDeRetiro() const;
    void setFechaDeRetiro(int fechaDeRetiro);
    char getTipo() const;
    void setTipo(char tipo);
private:
    int carne;
    char tipo;
    char *codigoLib;
    int fechaDeRetiro;
    int deuda;
};

ifstream& operator >>(ifstream& arch, LibroPrestado& libPrest);
ofstream& operator <<(ofstream& arch, LibroPrestado& libPrest);

#endif /* LIBROPRESTADO_H */
