/*
 * File:   funciones.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 18 de abril de 2022, 08:34 PM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "funciones.h"
using namespace std;

void generarReporte() {
    double descCatA, descCatB, descCatC, mayDesc = 0, totalVerif = 0;
    char codProdVerif[8], descProdVerif[45] = {0}, nomCliMayDesc[45];
    // Imprimir cabecera y leer datos de inicio
    imprimirCabeceraReporte();
    leerDatosInicio(descCatA, descCatB, descCatC, codProdVerif);
    procesarClientes(descCatA, descCatB, descCatC, nomCliMayDesc, mayDesc,
            codProdVerif, descProdVerif, totalVerif);
    imprimirResumenReporte(nomCliMayDesc, mayDesc, descProdVerif, codProdVerif,
            totalVerif);
}

void leerDatosInicio(double& descCatA, double& descCatB, double& descCatC,
        char* codProdVerif) {
    char c;
    cin >> c >> descCatA >> c >> ws;
    cin >> c >> descCatB >> c >> ws;
    cin >> c >> descCatC >> c >> ws;
    cin >> codProdVerif;
}

void imprimirCabeceraReporte() {
    cout << fixed << setprecision(2);
    cout << setw(78) << "EMPRESA COMERCIALIZADORA DE ABARROTES" << endl;
    imprimirLinea('=');
    cout << "GASTOS DE LOS CLIENTES REGISTRADOS:" << endl;
}

void procesarClientes(double descCatA, double descCatB, double descCatC,
        char* nomCliMayDesc, double& mayDesc, char* codProdVerif,
        char* descProdVerif, double& totalVerif) {
    double descCli, descAdi, cantProd, precUnit, totalPagar = 0, totalDesc = 0;
    char nomCli[45], codProd[8], descProd[45], catCli, c;
    int dni, telef, dd, mm, aaaa, indice = 0;
    // Leer cliente por cliente
    while (true) {
        cin >> dni; // Intentamos leer un DNI
        if (cin.eof()) break;
        if (cin.fail()) {
            cin.clear();
            // Si la lectura del DNI falla, leer producto por producto
            cin >> codProd >> ws >> descProd >> ws >> cantProd;
            if (cin.fail()) {
                cin.clear();
                // Leer descuento adicional antes de la cantidad del producto
                cin >> c >> descAdi >> cantProd;
            } else {
                descAdi = 0;
            }
            cin >> precUnit >> dd >> c >> mm >> c >> aaaa;
            imprimirProducto(indice, codProd, descProd, precUnit, cantProd,
                    descCli, descAdi, totalPagar, totalDesc, dd, mm, aaaa,
                    codProdVerif, descProdVerif, totalVerif);
        } else {
            if (indice > 0)
                imprimirResumenProductos(indice, totalPagar, totalDesc,
                        nomCliMayDesc, mayDesc, nomCli);
            else
                indice = 1;
            cin >> ws >> nomCli >> telef >> ws;
            procesarNombreCliente(nomCli, descCatA, descCatB, descCatC, catCli,
                    descCli);
            imprimirCliente(dni, nomCli, telef, catCli, descCli);
            imprimirCabeceraProductos();
        }
    }
    imprimirResumenProductos(indice, totalPagar, totalDesc, nomCliMayDesc,
            mayDesc, nomCli);
}

void procesarNombreCliente(char* nombre, double descCatA, double descCatB,
        double descCatC, char& catCli, double& descCli) {
    // Obtener la longitud de la cadena
    int tam = strlen(nombre);
    // Si el nombre tiene un guión en el penúltimo
    if (nombre[tam-2] == '-') {
        catCli = nombre[tam-1];
        switch (catCli) {
            case 'A':
                descCli = descCatA;
                break;
            case 'B':
                descCli = descCatB;
                break;
            case 'C':
                descCli = descCatC;
                break;
        }
        nombre[tam-2] = 0;
    } else {
        catCli = '-';
        descCli = 0;
    }
    // Reemplazar los guiones y otros caracteres por espacios
    reemplazarGuiones(nombre);
}

void imprimirCliente(int dni, char* nomCli, int telef, char catCli, double descCli) {
    // Imprimir cabecera del cliente
    imprimirLinea('=');
    cout << left << setw(10) << "DNI" << setw(45) << "Nombre"
            << setw(12) << "Telefono" << setw(15) << "Categoria"
            << "Descuento" << endl;
    // Imprimir datos del cliente
    cout << setw(10) << dni << setw(45) << nomCli << setw(10) << telef
            << right << setw(7) << catCli;
    imprimirDescuento(descCli, 16);
    cout << '%' << endl;
    imprimirLinea('-');
}

void imprimirDescuento(double desc, int tam) {
    if (desc > 0)
        cout << setw(tam) << desc;
    else
        cout << setw(tam) << "-.--";
}

void imprimirCabeceraProductos() {
    cout << "PRODUCTOS ADQUIRIDOS:" << endl;
    imprimirLinea('-');
    cout << left << setw(5) << ' ' << setw(8) << "Codigo"
            << setw(45) << "Descripcion" << right << "P.U."
            << setw(12) << "Cantidad" << setw(9) << "Total"
            << setw(15) << "Descuentos %" << setw(11) << "A Pagar"
            << setw(11) << "Descuento" << setw(11) << "Fecha" << endl;
    imprimirLinea('-');
}

void imprimirProducto(int& indice, char* codProd, char* descProd,
        double precUnit, double cantProd, double descCli, double descAdi,
        double& totalPagar, double& totalDesc, int dd, int mm, int aaaa,
        char* codProdVerif, char* descProdVerif, double& totalVerif) {
    double total, aPagar, desc;
    // Calcular los datos intermedios
    total = precUnit*cantProd;
    aPagar = total*((100.0-descAdi)/100.0)*((100-descCli)/100.0);
    desc = total - aPagar;
    reemplazarGuiones(descProd);
    // Imprimir los datos del producto
    cout << right << setw(3) << indice << setw(2) << ' '
            << left << setw(8) << codProd << setw(42) << descProd
            << right << setw(8) << precUnit << setw(10) << cantProd
            << setw(10) << total;
    imprimirDescuento(descAdi, 8);
    cout << " | ";
    imprimirDescuento(descCli, 5);
    cout << setw(10) << aPagar << setw(10) << desc << setw(5) << ' '
            << setfill('0') << setw(2) << dd << '/' << setw(2) << mm << '/'
            << setw(4) << aaaa << setfill(' ') << endl;
    // Actualizar contadores
    indice++;
    totalPagar += aPagar;
    totalDesc += desc;
    if (strcmp(codProd, codProdVerif) == 0) {
        if (strlen(descProdVerif) == 0)
            strcpy(descProdVerif, descProd);
        totalVerif += aPagar;
    }
}

void imprimirResumenProductos(int& indice, double& totalPagar, double& totalDesc,
        char* nomCliMayDesc, double& mayDesc, char* nomCli) {
    // Imprimir los contadores
    imprimirLinea('-');
    cout << right << setw(11) << "TOTAL:" << setw(98) << totalPagar
            << setw(10) << totalDesc << endl;
    imprimirLinea('=');
    cout << endl;
    // Verificar si es el cliente con mayor descuento
    if (totalDesc > mayDesc) {
        mayDesc = totalDesc;
        strcpy(nomCliMayDesc, nomCli);
    }
    // Reiniciar los contadores
    indice = 1;
    totalPagar = 0;
    totalDesc = 0;
}

void imprimirResumenReporte(char* nomCliMayDesc, double mayDesc,
        char* descProdVerif, char* codProdVerif, double totalVerif) {
    cout << left << "CLIENTE QUE RECIBIO MAS DESCUENTO: "
            << setw(48) << nomCliMayDesc << "DESCUENTO TOTAL: "
            << right << setw(9) << mayDesc << endl;
    cout << left << "PRODUCTO A VERIFICAR: " << descProdVerif
            << " [" << codProdVerif << ']' << right << setw(45)
            << "TOTAL INGRESADO POR EL PRODUCTO: "
            << setw(9) << totalVerif << endl;
}

/* Funciones auxiliares */

void imprimirLinea(char c) {
    for (int i = 0; i < 140; i++) cout << c;
    cout << endl;
}

void reemplazarGuiones(char* cadena) {
    for (int i = 0; cadena[i] != 0; i++) {
        if (cadena[i] == '/' || cadena[i] == '_' || cadena[i] == '-')
            cadena[i] = ' ';
    }
}
