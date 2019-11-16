/* 
 * Archivo: NumeroMuyGrande.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 01:10 PM
 */

#include "NumeroMuyGrande.h"
#include <iostream>
#include <cstring>
using namespace std;

// Inicialización

NumeroMuyGrande::NumeroMuyGrande() {
    this->digitos = NULL;
    this->longitud = 0;
    this->signo = '+';
}

NumeroMuyGrande::NumeroMuyGrande(const char* cadena) {
    this->digitos = NULL;
    this->asignar(cadena);
}

NumeroMuyGrande::NumeroMuyGrande(NumeroMuyGrande& numero) {
    this->digitos = NULL;
    this->asignar(numero);
}

// Asignación

void NumeroMuyGrande::asignar(const char* cadena) {
    // Determinar signo, longitud y comienzo de las digitos
    int longitud = strlen(cadena);
    if (cadena[0] == '+') {
        this->signo = '+';
        this->longitud = longitud - 1;
    } else if (cadena[0] == '-') {
        this->signo = '-';
        this->longitud = longitud - 1;
    } else {
        this->signo = '+';
        this->longitud = longitud;
    }
    // Limpiar los dígitos anteriores, si es que existen
    this->limpiar();
    // Escribir dígitos en orden invertido
    this->digitos = new char[this->longitud];
    for (int i = 0; i < this->longitud; i++) {
        this->digitos[i] = cadena[longitud - i - 1] - '0';
    }
}

void NumeroMuyGrande::asignar(NumeroMuyGrande& numero) {
    // Copiar signo y longitud
    this->signo = numero.signo;
    this->longitud = numero.longitud;
    // Limpiar los dígitos anteriores, si es que existen
    this->limpiar();
    // Copiar dígitos de un objeto en otro
    this->digitos = new char[this->longitud];
    for (int i = 0; i < this->longitud; i++) {
        this->digitos[i] = numero.digitos[i];
    }
}

void NumeroMuyGrande::operator =(const char* cadena) {
    this->asignar(cadena);
}

void NumeroMuyGrande::operator =(NumeroMuyGrande& numero) {
    this->asignar(numero);
}

// Operaciones

const NumeroMuyGrande& NumeroMuyGrande::operator +(NumeroMuyGrande& numero) {
    // Caso 1: Son del mismo signo
    if (this->signo == numero.signo) {
        return this->sumar(numero, this->signo);
    }
    // Caso 2: Son de signos diferentes
    // return NumeroMuyGrande("0");
}

const NumeroMuyGrande& NumeroMuyGrande::operator -(NumeroMuyGrande& numero) {
    // Caso 1: Son de signos diferentes
    if (this->signo != numero.signo) {
        return this->sumar(numero, this->signo);
    }
    // Caso 2: Son de signos iguales
    // return NumeroMuyGrande("0");
}

const NumeroMuyGrande& NumeroMuyGrande::sumar(NumeroMuyGrande& numero, char signo) {
    // Inicializar datos del resultado
    NumeroMuyGrande resultado;
    resultado.longitud = this->mayorLongitud(numero);
    resultado.digitos = new char[resultado.longitud + 1];
    resultado.signo = signo;
    // Sumar los dígitos
    char carry = 0, digito;
    for (int i = 0; i < this->longitud && i < numero.longitud; i++) {
        // Calcular el dígito
        digito = carry;
        if (i < this->longitud) digito += this->digitos[i];
        if (i < numero.longitud) digito += numero.digitos[i];
        // Actualizar arreglo de dígitos y carry
        resultado.digitos[i] = digito % 10;
        carry = digito / 10;
    }
    // Ver si sobró un dígito para ser asignado
    if (carry == 0) {
        char* digitos = new char[resultado.longitud];
        for (int i = 0; i < resultado.longitud; i++) {
            digitos[i] = resultado.digitos[i];
        }
        delete[] resultado.digitos;
        resultado.digitos = digitos;
    } else {
        resultado.digitos[resultado.longitud] = 1;
    }
    // Devolver el objeto con las variables proporcionadas
    return resultado;
}

// Comparación

int NumeroMuyGrande::comparar(NumeroMuyGrande& numero) {
    // Caso 1: Ambos números tienen signos diferentes
    if (this->signo != numero.signo) {
        return (this->signo == '+') ? 1 : -1;
    }
    // Caso 2: La longitud de este número es menor que la del parámetro
    if (this->longitud < numero.longitud) {
        return (this->signo == '+') ? -1 : 1;
    }
    // Caso 3: La longitud de este número es mayor que la del parámetro
    if (this->longitud > numero.longitud) {
        return (this->signo == '+') ? 1 : -1;
    }
    // Caso 4: El signo y la longitud de ambos números son iguales
    for (int i = 0; i < this->longitud; i++) {
        if (this->digitos[i] < numero.digitos[i]) {
            return (this->signo == '+') ? -1 : 1;
        }
        if (this->digitos[i] > numero.digitos[i]) {
            return (this->signo == '+') ? 1 : -1;
        }
    }
    // Caso 5: Son el mismo número
    return 0;
}

bool NumeroMuyGrande::operator ==(NumeroMuyGrande& numero) {
    return this->comparar(numero) == 0;
}

bool NumeroMuyGrande::operator >(NumeroMuyGrande& numero) {
    return this->comparar(numero) > 0;
}

bool NumeroMuyGrande::operator <(NumeroMuyGrande& numero) {
    return this->comparar(numero) < 0;
}

// Otros métodos

int NumeroMuyGrande::length() {
    return this->longitud;
}

ifstream& NumeroMuyGrande::leer(ifstream& archivo) {
    // TODO
    return archivo;
}

ofstream& NumeroMuyGrande::imprimir(ofstream& archivo) {
    // Colocar espacios antes del número
    int espacios = archivo.width() - this->longitud - 1;
    for (int i = 0; i < espacios; i++) {
        archivo.put(' ');
    }
    // Colocar representación del número
    if (this->longitud == 0) {
        archivo.put('0');
    } else {
        archivo.put(this->signo);
        for (int i = this->longitud - 1; i >= 0; i--) {
            char c = this->digitos[i] + '0';
            archivo.put(c);
        }
    }
    return archivo;
}

NumeroMuyGrande::~NumeroMuyGrande() {
    this->limpiar();
}

// Métodos auxiliares

int NumeroMuyGrande::mayorLongitud(NumeroMuyGrande& numero) {
    return this->longitud > numero.longitud ? this->longitud : numero.longitud;
}

void NumeroMuyGrande::limpiar() {
    if (this->digitos != NULL) {
        delete[] this->digitos;
    }
}
