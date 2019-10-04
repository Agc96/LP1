/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 03:35 PM
 */

#include "funciones.h"
using namespace std;

void jpPruebaCadenas() {
    ifstream prueba("files/Prueba.txt", ios::in);
    if (!prueba) {
        cerr << "No se pudo abrir el archivo de prueba de cadenas." << endl;
        exit(1);
    }
    ofstream reporte("files/Reporte.txt", ios::out);
    if (!reporte) {
        cerr << "No se pudo crear el reporte de prueba de cadenas." << endl;
        exit(1);
    }

    Cadena cad01, cad02, cad03, cad04, cad05, cad06, cad07;

    reporte << "Prueba de inicialización y longitud" << endl;
    inicializa(cad01);
    jpImprimirCadena(reporte, cad01, "Nada"); // (0)
    inicializa(cad01, '*');
    jpImprimirCadena(reporte, cad01, "100 guiones");
    inicializa(cad01, '#', 20);
    jpImprimirCadena(reporte, cad01, "20 numerales");
    inicializa(cad01, '&', 120);
    jpImprimirCadena(reporte, cad01, "Desbordamiento"); // (-1)
    reporte << endl;

    reporte << "Prueba de lectura y recorte de cadenas" << endl;
    leer(prueba, cad01, '#');
    jpImprimirCadena(reporte, cad01, "Antes del recorte"); // [ws]Juan[ws]Perez[ws]Lopez[ws] (64)
    recortar(cad01);
    jpImprimirCadena(reporte, cad01, "Despues del recorte"); // Juan Perez Lopez (16)
    reporte << endl;

    reporte << "Prueba de intercambiar cadenas" << endl;
    leer(prueba, cad01, '#');
    jpImprimirCadena(reporte, cad01, "Primera cadena"); // "Esta va a ser la primera cadena"
    leer(prueba, cad02);
    jpImprimirCadena(reporte, cad02, "Segunda cadena"); // "Esta cadena debería ser intercambiada con la anterior"
    intercambiar(cad01, cad02);
    jpImprimirCadena(reporte, cad01, "Primera cadena");
    jpImprimirCadena(reporte, cad02, "Segunda cadena");
    reporte << endl;

    reporte << "Pruebas de lectura e impresión usando operadores >> y <<" << endl;
    prueba >> cad01;
    reporte << cad01 << endl << endl; // Esta cadena deberia leerse y luego copiarse usando sobrecarga de operadores

    reporte << " Prueba de asignacion usando operador &" << endl;
    (cad02)&(cad01);
    jpImprimirCadena(reporte, cad01, "Primera cadena");
    jpImprimirCadena(reporte, cad02, "Segunda cadena");
    reporte << endl;

    reporte << "Prueba de agregación usando operador +=" << endl;
    leer(prueba, cad03, '#');
    jpImprimirCadena(reporte, cad03, "Primera cadena"); // Esta es la primera parte de la primera cadena larga
    leer(prueba, cad04);
    jpImprimirCadena(reporte, cad04, "Segunda cadena"); // , y aqui se vienen mas caracteres
    cad03 += cad04;
    jpImprimirCadena(reporte, cad03, "Primera cadena"); // Esta es la primera parte de la primera cadena larga, y aqui se vienen mas caracteres
    reporte << endl;

    reporte << "Prueab de agregación usando operador +" << endl;
    leer(prueba, cad05, '#');
    jpImprimirCadena(reporte, cad05, "Primera cadena"); // Esta es la primera parte de la segunda cadena larga
    leer(prueba, cad06);
    jpImprimirCadena(reporte, cad06, "Segunda cadena"); // , y aqui se vienen mas caracteres
    cad07 = cad05 + cad06;
    jpImprimirCadena(reporte, cad07, "Tercera cadena"); // Esta es la primera parte de la segunda cadena larga, y aqui se vienen mas caracteres
    reporte << endl;

    reporte << "Prueba de comparación usando operadores ==, <, >" << endl;
    jpImprimirComparacion(reporte, cad01 == cad02, "¿cad01 == cad02?"); // Verdadero
    jpImprimirComparacion(reporte, cad04 == cad06, "¿cad04 == cad06?"); // Verdadero
    jpImprimirComparacion(reporte, cad05 == cad07, "¿cad05 == cad07?"); // Falso
    jpImprimirComparacion(reporte, cad03 < cad07, "¿cad03 < cad07?"); // Verdadero
    jpImprimirComparacion(reporte, cad01 < cad03, "¿cad01 < cad03?"); // Verdadero
    jpImprimirComparacion(reporte, cad04 < cad06, "¿cad04 < cad06?"); // Falso
    jpImprimirComparacion(reporte, cad05 > cad06, "¿cad05 > cad06?"); // Verdadero
    jpImprimirComparacion(reporte, cad07 > cad05, "¿cad07 > cad05?"); // Verdadero
    jpImprimirComparacion(reporte, cad04 > cad06, "¿cad04 > cad06?"); // Falso
}

void jpImprimirCadena(ofstream& reporte, Cadena& cadena, const char* titulo) {
    reporte << "- " << titulo << ": \"";
    imprimir(reporte, cadena);
    reporte << "\" (longitud = " << longitud(cadena) << ")" << endl;
}

void jpImprimirComparacion(ofstream& reporte, bool resultado, const char* titulo) {
    reporte << "- " << titulo << ": " << ((resultado) ? "Verdadero" : "Falso") << endl;
}
