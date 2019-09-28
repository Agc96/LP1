/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 03:35 PM
 */

#include "funciones.h"
#include "cadena.h"
#define MAX_LINEA 120
using namespace std;

void pruebaInicializacionLongitud(ofstream& resultado) {
    Cadena cadena;
    
    resultado << "Prueba de inicialización y longitud" << endl;
    separacion(resultado, '-');
    
    inicializa(cadena);
    imprimirDetalle(resultado, cadena); // Nada (0)
    
    inicializa(cadena, '#', 20);
    imprimirDetalle(resultado, cadena); // 20 numerales (20)
    
    inicializa(cadena, '*');
    imprimirDetalle(resultado, cadena); // 100 guiones (100)
    
    inicializa(cadena, '&', 120);
    imprimirDetalle(resultado, cadena); // [Desbordamiento] (-1)
    
    separacion(resultado, '=');
}

void pruebaRecortarCadenas(ofstream& resultado, ifstream& prueba) {
    Cadena cadena;
    
    resultado << "Prueba de recortar cadenas" << endl;
    separacion(resultado, '-');
    
    leer(prueba, cadena, '#');
    imprimirDetalle(resultado, cadena); // [ws]Juan[ws]Perez[ws]Lopez[ws] (64)
    
    recortar(cadena);
    imprimirDetalle(resultado, cadena); // Juan Perez Lopez (16)
    
    separacion(resultado, '=');
}

void pruebaIntercambiarCadenas(ofstream& resultado, ifstream& prueba) {
    Cadena cad01, cad02;
    
    resultado << "Prueba de intercambiar cadenas" << endl;
    separacion(resultado, '-');
    
    resultado << "- Lectura de la primera cadena" << endl;
    leer(prueba, cad01, '#');
    imprimirDetalle(resultado, cad01); // "Esta va a ser la primera cadena"
    
    resultado << "- Lectura de la segunda cadena" << endl;
    leer(prueba, cad02);
    imprimirDetalle(resultado, cad02); // "Esta cadena debería ser intercambiada con la anterior"
    
    resultado << "- Intercambio de cadenas:" << endl;
    intercambiar(cad01, cad02);
    imprimirDetalle(resultado, cad01);
    imprimirDetalle(resultado, cad02);
    
    separacion(resultado, '=');
}

void pruebaSobrecarga(ofstream& resultado, ifstream& prueba) {
    Cadena cad01, cad02, cad03, cad04, cad05, cad06, cad07;
    
    resultado << "Prueba de sobrecarga de operadores" << endl;
    separacion(resultado, '-');
    
    resultado << "- Lectura e impresión usando operadores >> y <<" << endl;
    prueba >> cad01;
    resultado << cad01 << endl;
    
    resultado << " - Asignacion usando operador &" << endl;
    cad02 & cad01;
    imprimirDetalle(resultado, cad01);
    imprimirDetalle(resultado, cad02);
    
    resultado << "- Agregación usando operador +=" << endl;
    leer(prueba, cad03, '#');
    imprimirDetalle(resultado, cad03);
    leer(prueba, cad04);
    imprimirDetalle(resultado, cad04);
    cad03 += cad04;
    imprimirDetalle(resultado, cad03);
    
    resultado << "- Agregación usando operador +" << endl;
    leer(prueba, cad05, '#');
    imprimirDetalle(resultado, cad05);
    leer(prueba, cad06);
    imprimirDetalle(resultado, cad06);
    cad07 = cad05 + cad06;
    imprimirDetalle(resultado, cad07);
    
    resultado << "- Comparación usando operadores ==, <, >" << endl;
    resultado << "  - ¿cad01 == cad02? " << (cad01 == cad02) << endl;
    resultado << "  - ¿cad03 < cad07? " << (cad03 < cad07) << endl;
    resultado << "  - ¿cad05 > cad06? " << (cad05 > cad06) << endl;
}

void imprimirDetalle(ofstream& archivo, Cadena& cadena) {
    archivo << "Cadena: \"";
    imprimir(archivo, cadena);
    archivo << "\" (longitud = " << longitud(cadena) << ")" << endl;
}

void separacion(ofstream& archivo, char car) {
    for (int i = 0; i < MAX_LINEA; i++) {
        archivo.put(car);
    }
    archivo << endl;
}
