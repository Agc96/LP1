/* 
 * Archivo: cadena.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 26 de septiembre de 2019, 05:48 PM
 */

#include <cstdlib>
#include <cctype>
#include "cadena.h"

void inicializa(Cadena& cadena, int capacidad) {
    cadena.longitud = 0;
    if (capacidad > 0) {
        cadena.capacidad = capacidad;
        cadena.cadena = new char[capacidad];
    } else {
        cadena.capacidad = 0;
        cadena.cadena = NULL;
    }
}

istream& leer(istream& in, Cadena& cadena, char caracterParada) {
    cadena.longitud = 0;
    char caracterLeido;
    while ((caracterLeido = in.get()) != caracterParada) {
        if (cadena.longitud >= cadena.capacidad) {
            cadena.capacidad = cadena.longitud + 1;
            char* temp = new char[cadena.capacidad];
            if (cadena.cadena != NULL) {
                for (int i = 0; i < cadena.longitud; i++) {
                    temp[i] = cadena.cadena[i];
                }
                delete[] cadena.cadena;
            }
            cadena.cadena = temp;
        }
        cadena.cadena[cadena.longitud++] = caracterLeido;
    }
    return in;
}

void leer(Cadena& cadena, char caracterParada) {
    leer(cin, cadena, caracterParada);
}

ostream& imprimir(ostream& out, Cadena& cadena) {
    out << "Cadena (longitud: " << cadena.longitud << ", capacidad: "
        << cadena.capacidad << ", texto: \"";
    for (int i = 0; i < cadena.longitud; i++) {
        cout.put(cadena.cadena[i]);
    }
    out << "\")" << endl;
    return out;
}

void imprimir(Cadena& cadena) {
    imprimir(cout, cadena);
}

int longitud(Cadena& cadena) {
    return cadena.longitud;
}

int capacidad(Cadena& cadena) {
    return cadena.capacidad;
}

void recortar(Cadena& cadena) {
    char* temp = new char[cadena.longitud];
    int nuevaLongitud = 0, inicio, fin;
    // Calcular inicio y fin de la cadena
    for (inicio = 0; inicio < cadena.longitud && isspace(cadena.cadena[inicio]); inicio++);
    for (fin = cadena.longitud - 1; fin >= 0 && isspace(cadena.cadena[fin]); fin--);
    cout << "Inicio es " << inicio << ", fin es " << fin << endl;
    // Escribir cadena
    for (int i = inicio; i <= fin; i++) {
        if (isspace(cadena.cadena[i])) {
            if ((i + 1) < cadena.longitud && !isspace(cadena.cadena[i + 1])) {
                temp[nuevaLongitud++] = ' ';
            }
        } else {
            temp[nuevaLongitud++] = cadena.cadena[i];
        }
    }
    // Reemplazar cadena
    delete[] cadena.cadena;
    cadena.cadena = temp;
    cadena.capacidad = cadena.longitud;
    cadena.longitud = nuevaLongitud;
}

void intercambiar(Cadena& cadena1, Cadena& cadena2) {
    // Guardar los datos de la estructura
    char* tempCadena = cadena1.cadena;
    int tempLongitud = cadena1.longitud;
    int tempCapacidad = cadena1.capacidad;
    // Asignar elementos de cadena2 en cadena1
    cadena1.cadena = cadena2.cadena;
    cadena1.longitud = cadena2.longitud;
    cadena1.capacidad = cadena2.capacidad;
    // Asignar elementos de cadena1 en cadena2
    cadena2.cadena = tempCadena;
    cadena2.longitud = tempLongitud;
    cadena2.capacidad = tempCapacidad;
}

/* operator = (Cadena& antigua) {
    Cadena nueva;
    nueva.longitud = antigua.longitud;
    nueva.capacidad = antigua.capacidad;
    nueva.cadena = new char[antigua.longitud];
    for (int i = 0; i < antigua.longitud; i++) {
        nueva.cadena[i] = antigua.cadena[i];
    }
} */

// Cadena operator += (Cadena);
/* Cadena operator + (Cadena& cadena1, Cadena& cadena2) {
    Cadena resultado;
    resultado.longitud = cadena1.longitud + cadena2.longitud;
    return resultado;
}

bool operator == (Cadena& cadena1, Cadena& cadena2) {
    return false;
}
bool operator > (Cadena, Cadena);
bool operator < (Cadena, Cadena);

*/

istream& operator >> (istream& in, Cadena& cadena) {
    return leer(in, cadena, '\n');
}

ostream& operator << (ostream& out, Cadena& cadena) {
    return imprimir(out, cadena);
}