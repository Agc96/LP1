/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 *
 * Created on 11 de septiembre de 2019, 03:05 PM
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <limits.h>
#include "constants.h"
#include "utilities.h"

using namespace std;

int main(int argc, char** argv) {
    // Declaración de variables
    int codigo, tamanhoNombre, dia, mes, anho, cantRetiros, cantDepositos,
            totalClientes;
    double dolarASoles, euroASoles, saldoInicial, fechaRetiros, fechaDepositos,
            saldoFinal, totalRetiros, totalDepositos, movimiento;
    char c, moneda;
    bool mayusculas, deposito;
    // Configurar cout e imprimir cabecera
    cout << left << fixed << setprecision(2);
    cout << "ESTADO DE CUENTAS DEL BANCO ABCD" << endl;
    // Leer tipos de cambio
    cin >> dolarASoles >> euroASoles;
    // Iterar entre todas las líneas
    totalClientes = 0;
    while (true) {
        c = cin.get();
        if (cin.eof()) break;
        // Leer e imprimir datos del cliente
        if (isalpha(c)) {
            // Inicializar valores
            totalClientes++;
            cantRetiros = 0;
            cantDepositos = 0;
            totalRetiros = 0;
            totalDepositos = 0;
            saldoFinal = saldoInicial;
            // Imprimir cabecera
            cout << left << setw(MAX_NOMBRE) << "CLIENTE";
            cout << setw(MAX_CUENTA) << "CODIGO DE CUENTA";
            cout << setw(MAX_MONEDA) << "MONEDA" << "SALDO INICIAL" << endl;
            // Escribir el nombre del cliente hasta encontrar el código 
            cout.put(c);
            tamanhoNombre = 1;
            mayusculas = false;
            while (true) {
                c = cin.get();
                if (c == ' ') {
                    // Intentar leer el código
                    if (cin >> codigo) break;
                    // Si no se pudo, continuar leyendo el nombre
                    cin.clear();
                    cout.put(' ');
                    mayusculas = true;
                } else {
                    if (mayusculas) {
                        cout.put(c);
                        mayusculas = false;
                    } else {
                        cout.put(tolower(c));
                    }
                }
                tamanhoNombre++;
            }
            espacios(MAX_NOMBRE - tamanhoNombre);
            // Leer y escribir código de cuenta
            cout << setw(MAX_CUENTA) << codigo;
            // Leer y escribir moneda
            while (' ' == (moneda = cin.get()));
            cout << setw(MAX_MONEDA);
            imprimirMoneda(moneda);
            // Leer y escribir saldo inicial
            cin >> saldoInicial;
            cout << moneda << ' ' << saldoInicial << endl;
            separacion('=');
            // Colocar cabecera de movimientos
            cout << setw(MAX_FECHA) << "FECHA";
            cout << "RETIROS " << setw(MAX_SALDO - 8);
            imprimirMoneda(moneda);
            cout << "DEPOSITOS " << setw(MAX_SALDO - 10);
            imprimirMoneda(moneda);
            cout << "SALDO " << setw(MAX_SALDO - 6);
            imprimirMoneda(moneda);
            cout << "OBSERVACION" << endl;
            separacion('-');
            // Ignorar caracteres hasta el cambio de línea
            while ((c = cin.get()) != '\n');
        }
        // Leer e imprimir movimientos del día
        else if (c == ' ') {
            // Inicializar valores
            fechaDepositos = 0;
            fechaRetiros = 0;
            // Leer y escribir día
            cin >> dia >> c >> mes >> c >> anho;
            cout << setfill('0') << setw(2) << dia << '/' << setw(2) << mes;
            cout << '/' << setw(4) << anho << setfill(' ');
            // Leer caracteres hasta el cambio de línea
            while ((c = cin.get()) != '\n') {
                switch (c) {
                    case 'D':
                        deposito = true;
                        continue;
                    case 'R':
                        deposito = false;
                        continue;
                    case 'S':
                        cin >> movimiento;
                        switch (moneda) {
                            // Convertir de soles a dólares
                            case '$':
                                movimiento /= dolarASoles;
                                break;
                            // Convertir de soles a euros
                            case '&':
                                movimiento /= euroASoles;
                                break;
                        }
                        break;
                    case '$':
                        cin >> movimiento;
                        switch (moneda) {
                            // Convertir de dólares a soles
                            case 'S':
                                movimiento *= dolarASoles;
                                break;
                            // Convertir de dólares a euros
                            case '&':
                                movimiento *= dolarASoles / euroASoles;
                                break;
                        }
                        break;
                    case '&':
                        cin >> movimiento;
                        switch (moneda) {
                            // Convertir de euros a soles
                            case 'S':
                                movimiento *= euroASoles;
                                break;
                            // Convertir de euros a dólares
                            case '$':
                                movimiento *= euroASoles / dolarASoles;
                                break;
                        }
                        break;
                    default:
                        continue;
                }
                // Guardar movimiento
                if (deposito) {
                    cantDepositos++;
                    fechaDepositos += movimiento;
                    totalDepositos += movimiento;
                } else {
                    cantRetiros++;
                    fechaRetiros += movimiento;
                    totalRetiros += movimiento;
                }
            }
            saldoFinal += fechaDepositos - fechaRetiros;
            // Imprimir resumenes
            espacios(5);
            cout << moneda << right << setw(MAX_DECIMAL) << fechaRetiros;
            espacios(MAX_SALDO - MAX_DECIMAL - 1);
            cout << moneda << right << setw(MAX_DECIMAL) << fechaDepositos;
            espacios(MAX_SALDO - MAX_DECIMAL - 1);
            cout << moneda << right << setw(MAX_DECIMAL) << saldoFinal;
            espacios(MAX_SALDO - MAX_DECIMAL - 1);
            if (saldoFinal < 0) {
                cout << "SOBREGIRO";
            } else if (saldoFinal < MIN_ESTADO) {
                cout << "BAJO EL MINIMO";
            }
            cout << endl;
        }
        // Imprimir resumen de nuevo cliente
        else if (c == '\n') {
            if (totalClientes > 0) {
                separacion('=');
                cout << "RESUMEN:" << endl;
                // Resumen de retiros
                cout << left << setw(MAX_RESUMEN) << "CANTIDAD TOTAL DE RETIROS:";
                cout << right << setw(MAX_ENTERO) << cantRetiros;
                cout << setw(MAX_RESUMEN) << "TOTAL DE RETIROS: ";
                cout << moneda << setw(MAX_DECIMAL) << totalRetiros << endl;
                // Resumen de depósitos
                cout << left << setw(MAX_RESUMEN) << "CANTIDAD TOTAL DE DEPOSITOS:";
                cout << right << setw(MAX_ENTERO) << cantDepositos;
                cout << setw(MAX_RESUMEN) << "TOTAL DE DEPOSITOS: ";
                cout << moneda << setw(MAX_DECIMAL) << totalDepositos << endl;
                // Resumen de saldo
                cout << left << setw(MAX_RESUMEN) << "SALDO FINAL: ";
                cout << right << moneda << setw(MAX_DECIMAL) << saldoFinal;
                cout << setw(MAX_RESUMEN) << "OBSERVACION FINAL: ";
                if (saldoFinal < 0) {
                    cout << "CUENTA EN SOBREGIRO";
                } else if (saldoFinal < MIN_ESTADO) {
                    cout << "CUENTA BAJO EL MINIMO";
                }
                cout << endl;
            }
            separacion('=');
        }
    }
    
    return 0;
}

