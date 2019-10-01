/* 
 * Archivo: cadena.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 12:43 PM
 */

#include "cadena.h"
using namespace std;

void inicializa(Cadena& cadena, char car, int cant) {
    if (cant <= MAX_CADENA) {
        if (car != '\0') {
            for (int i = 0; i < cant; i++) {
                cadena.cadena[i] = car;
            }
            cadena.longitud = cant;
        } else {
            cadena.longitud = 0;
        }
        cadena.overF = false;
    } else {
        cadena.overF = true;
    }
}

void inicializa(Cadena& cadena) {
    cadena.longitud = 0;
    cadena.overF = false;
}

void leer(ifstream& arch, Cadena& cadena, char car) {
    for (cadena.longitud = 0; arch && cadena.longitud < MAX_CADENA; cadena.longitud++) {
        // Leer uno a uno los caracteres
        cadena.cadena[cadena.longitud] = arch.get();
        // Ver si llegamos al caracter de parada
        if (cadena.cadena[cadena.longitud] == car) {
            cadena.overF = false;
            return;
        }
    }
    // Detenemos la lectura y colocamos desborde
    cadena.overF = true;
}

void imprimir(ofstream& arch, Cadena& cadena) {
    if (cadena.overF) {
        arch << "[Desbordamiento]";
    } else {
        for (int i = 0; i < cadena.longitud; i++) {
            arch << cadena.cadena[i];
        }
    }
}

int longitud(Cadena& cadena) {
    return cadena.overF ? -1 : cadena.longitud;
}

void recortar(Cadena& cadena) {
    if (cadena.overF) return;
    // Obtener inicio y fin de la cadena
    int inicio, fin, longitud = 0;
    for (inicio = 0; inicio < cadena.longitud; inicio++) {
        if (!isspace(cadena.cadena[inicio])) break;
    }
    for (fin = cadena.longitud - 1; fin >= 0; fin--) {
        if (!isspace(cadena.cadena[fin])) break;
    }
    // Recortar cadena y recortar espacios dentro de la cadena
    for (int i = inicio; i <= fin; i++) {
        if (!isspace(cadena.cadena[i])) {
            cadena.cadena[longitud++] = cadena.cadena[i];
        } else if (!isspace(cadena.cadena[i - 1])) {
            cadena.cadena[longitud++] = ' ';
        }
    }
    cadena.longitud = longitud;
}

void intercambiar(Cadena& cad01, Cadena& cad02) {
    if (cad01.overF || cad02.overF) return;
    // Guardar referencias a la primera cadena
    int tempLongitud = cad01.longitud;
    char temp[MAX_CADENA];
    for (int i = 0; i < cad01.longitud; i++) {
        temp[i] = cad01.cadena[i];
    }
    // Reemplazar datos de la primera cadena con la segunda
    cad01.longitud = cad02.longitud;
    for (int i = 0; i < cad02.longitud; i++) {
        cad01.cadena[i] = cad02.cadena[i];
    }
    // Reemplazar datos de la segunda cadena con la primera
    cad02.longitud = tempLongitud;
    for (int i = 0; i < tempLongitud; i++) {
        cad02.cadena[i] = temp[i];
    }
}

Cadena& operator &(Cadena& cad01, Cadena& cad02) {
    if (!cad02.overF) {
        for (int i = 0; i < cad02.longitud; i++) {
            cad01.cadena[i] = cad02.cadena[i];
        }
        cad01.longitud = cad02.longitud;
        cad01.overF = false;
    }
    return cad01;
}

Cadena& operator +=(Cadena& cad01, const Cadena& cad02) {
    int totalLongitud = cad01.longitud + cad02.longitud;
    if (cad01.overF || cad02.overF || (totalLongitud > MAX_CADENA)) {
        cad01.overF = true;
    } else {
        for (int i = 0; i < cad02.longitud; i++) {
            cad01.cadena[cad01.longitud + i] = cad02.cadena[i];
        }
        cad01.longitud = totalLongitud;
        cad01.overF = false;
    }
    return cad01;
}

Cadena operator +(const Cadena& cad01, const Cadena& cad02) {
    Cadena cad03;
    int totalLongitud = cad01.longitud + cad02.longitud;
    if (cad01.overF || cad02.overF || (totalLongitud > MAX_CADENA)) {
        cad03.overF = true;
    } else {
        for (int i = 0; i < cad01.longitud; i++) {
            cad03.cadena[i] = cad01.cadena[i];
        }
        for (int i = 0; i < cad02.longitud; i++) {
            cad03.cadena[cad01.longitud + i] = cad02.cadena[i];
        }
        cad03.longitud = totalLongitud;
        cad03.overF = false;
    }
    return cad03;
}

int comparacion(const Cadena& cad01, const Cadena& cad02) {
    // Si las longitudes son diferentes, se comparan las longitudes
    int minLongitud = (cad01.longitud < cad02.longitud) ? cad01.longitud : cad02.longitud;
    // Comparar caracter por caracter
    for (int i = 0; i < minLongitud; i++) {
        if (cad01.cadena[i] != cad02.cadena[i]) {
            return cad01.cadena[i] - cad02.cadena[i];
        }
    }
    // Comparar las longitudes si es que una cadena es subcadena de la otra
    return cad01.longitud - cad02.longitud;
}

bool operator ==(const Cadena& cad01, const Cadena& cad02) {
    if (cad01.overF || cad02.overF) return false;
    return comparacion(cad01, cad02) == 0;
}
bool operator <(const Cadena& cad01, const Cadena& cad02) {
    if (cad01.overF || cad02.overF) return false;
    return comparacion(cad01, cad02) < 0;
}
bool operator >(const Cadena& cad01, const Cadena& cad02) {
    if (cad01.overF || cad02.overF) return false;
    return comparacion(cad01, cad02) > 0;
}

ifstream& operator >>(ifstream& arch, Cadena& cadena) {
    leer(arch, cadena, '\n');
    return arch;
}

ofstream& operator <<(ofstream& arch, Cadena& cadena) {
    if (!cadena.overF) {
        imprimir(arch, cadena);
    }
    return arch;
}
