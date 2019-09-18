/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez <anthony.gutierrez@pucp.pe>
 * Código:  20130095
 * Created on 13 de septiembre de 2019, 08:40 PM
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include "utilidades.h"
#define MAX_LINEA 100
#define MAX_NOMBRE 40
#define MAX_CABECERA 20
#define MAX_ENTERO 5
#define MAX_DECIMAL 15
#define MAX_RESUMEN 30
using namespace std;

int main(int argc, char** argv) {
    // Abrir los archivos
    ifstream movimientos("MovEnCuentas.txt", ios::in);
    if (!movimientos) {
        cerr << "No se pudo abrir el archivo de movimientos.";
        exit(1);
    }
    ifstream enero("Enero.txt", ios::in);
    if (!enero) {
        cerr << "No se pudo abrir el archivo de tipos de cambio de Enero.";
        exit(1);
    }
    ifstream febrero("Febrero.txt", ios::in);
    if (!febrero) {
        cerr << "No se pudo abrir el archivo de tipos de cambio de Febrero.";
        exit(1);
    }
    ifstream marzo("Marzo.txt", ios::in);
    if (!marzo) {
        cerr << "No se pudo abrir el archivo de tipos de cambio de Marzo.";
        exit(1);
    }
    ofstream reporte("Reporte.txt", ios::out);
    if (!reporte) {
        cerr << "No se pudo abrir el archivo del reporte.";
        exit(1);
    }
    // Declaración de variables
    int longCadena, codigo, dia, mes, anho, numRetiros, numDepositos;
    double cambioCliente, saldoInicial, saldoFinal, saldo, retiros, depositos,
            totalRetiros, totalDepositos, cambioMovimiento;
    char c, moneda;
    bool esRetiro, clienteLeido;
    // Imprimir cabecera
    reporte << left << fixed << setprecision(2);
    reporte << "ESTADO DE CUENTAS DEL BANCO ABCD" << endl;
    separacion(reporte, '=', MAX_LINEA);
    // Leer línea por línea
    while (true) {
        c = movimientos.get();
        if (movimientos.eof()) break;
        // Leer datos principales del cliente
        if (isalpha(c)) {
            // Escribir cabecera del cliente
            reporte << left << setw(MAX_NOMBRE) << "CLIENTE";
            reporte << setw(MAX_CABECERA) << "CODIGO DE CUENTA";
            reporte << setw(MAX_CABECERA) << "MONEDA";
            reporte << setw(MAX_CABECERA) << "SALDO INICIAL" << endl;
            // Escribir nombre del cliente
            reporte.put(c);
            longCadena = 1;
            // Intentar leer el código
            while (!(movimientos >> codigo)) {
                movimientos.clear();
                // Escribir nombre del cliente
                while ((c = movimientos.get()) != ' ') {
                    reporte.put(c);
                    longCadena++;
                }
                reporte.put(' ');
                longCadena++;
            }
            espacios(reporte, MAX_NOMBRE - longCadena);
            // Escribir el código
            reporte << setw(MAX_CABECERA) << codigo;
            // Leer la moneda
            while ((moneda = movimientos.get()) == ' ');
            longCadena = 0;
            // Obtener el nombre de la moneda
            enero.seekg(0, ios::beg);
            while (true) {
                c = enero.get();
                if (enero.eof()) break;
                // Verificar que es la moneda correcta
                if (c == moneda) {
                    enero >> cambioCliente;
                    // Leer y escribir el nombre de la moneda
                    while ((c = enero.get()) != '\n') {
                        if (c != ' ') {
                            reporte.put(c);
                            longCadena++;
                        }
                    }
                    espacios(reporte, MAX_CABECERA - longCadena);
                    break;
                }
                // Ir a la siguiente línea
                while ((c = enero.get()) != '\n');
            }
            // Leer y escribir el saldo inicial
            movimientos >> saldoInicial;
            reporte << moneda;
            reporte << right << setw(MAX_DECIMAL) << saldoInicial << endl;
            // Ir a la siguiente línea
            while ((c = movimientos.get()) != '\n');
            // Escribir la cabecera de los movimientos
            separacion(reporte, '=', MAX_LINEA);
            reporte << left << setw(MAX_CABECERA) << "FECHA";
            reporte << setw(MAX_RESUMEN) << "RETIROS";
            reporte << setw(MAX_RESUMEN) << "DEPOSITOS";
            reporte << "SALDO" << endl;
            separacion(reporte, '-', MAX_LINEA);
            // Inicializar variables para la siguiente fase
            clienteLeido = true;
            totalRetiros = 0;
            totalDepositos = 0;
            numRetiros = 0;
            numDepositos = 0;
            saldoFinal = saldoInicial;
        }
        // Leer movimientos por fecha del cliente
        else if (c == ' ') {
            // Inicializar variables
            retiros = 0;
            depositos = 0;
            // Leer y escribir fecha
            movimientos >> dia >> c >> mes >> c >> anho;
            reporte << setfill('0') << setw(2) << dia << '/';
            reporte << setw(2) << mes << '/';
            reporte << setw(4) << anho << setfill(' ');
            espacios(reporte, MAX_CABECERA - 10);
            // Obtener el tipo de cambio según el mes
            switch (mes) {
                case 1:
                    cambioCliente = obtenerTipoCambio(enero, moneda);
                    break;
                case 2:
                    cambioCliente = obtenerTipoCambio(febrero, moneda);
                    break;
                case 3:
                    cambioCliente = obtenerTipoCambio(marzo, moneda);
                    break;
            }
            // Leer caracteres hasta el cambio de línea
            while ((c = movimientos.get()) != '\n') {
                switch (c) {
                    case 'D':
                        esRetiro = false;
                        break;
                    case 'R':
                        esRetiro = true;
                        break;
                    case ' ':
                        break;
                    default:
                        // Leer saldo
                        movimientos >> saldo;
                        // Convertir saldo a moneda de la cuenta del cliente
                        if (c != moneda) {
                            switch (mes) {
                                case 1:
                                    cambioMovimiento = obtenerTipoCambio(enero, c);
                                    break;
                                case 2:
                                    cambioMovimiento = obtenerTipoCambio(febrero, c);
                                    break;
                                case 3:
                                    cambioMovimiento = obtenerTipoCambio(marzo, c);
                                    break;
                            }
                            saldo *= cambioMovimiento / cambioCliente;
                        }
                        // Adjuntar a retiros o depósitos
                        if (esRetiro) {
                            retiros += saldo;
                            numRetiros++;
                        } else {
                            depositos += saldo;
                            numDepositos++;
                        }
                        break;
                }
            }
            // Calcular totales
            totalRetiros += retiros;
            totalDepositos += depositos;
            saldoFinal += depositos - retiros;
            // Imprimir saldos
            reporte << right << moneda << setw(MAX_DECIMAL) << retiros;
            espacios(reporte, MAX_RESUMEN - MAX_DECIMAL - 1);
            reporte << moneda << setw(MAX_DECIMAL) << depositos;
            espacios(reporte, MAX_RESUMEN - MAX_DECIMAL - 1);
            reporte << moneda << setw(MAX_DECIMAL) << saldoFinal << endl;
        }
        // Escribir resumen del cliente
        else if (c == '\n') {
            if (clienteLeido) {
                separacion(reporte, '=', MAX_LINEA);
                reporte << left << "RESUMEN:" << endl;
                // Información de retiros
                reporte << setw(MAX_RESUMEN) << "CANTIDAD TOTAL DE RETIROS:";
                reporte << right << setw(MAX_ENTERO) << numRetiros;
                reporte << setw(MAX_RESUMEN) << "TOTAL DE RETIROS: ";
                reporte << moneda << setw(MAX_DECIMAL) << totalRetiros << endl;
                // Información de depósitos
                reporte << left << setw(MAX_RESUMEN) << "CANTIDAD TOTAL DE DEPOSITOS:";
                reporte << right << setw(MAX_ENTERO) << numDepositos;
                reporte << setw(MAX_RESUMEN) << "TOTAL DE DEPOSITOS: ";
                reporte << moneda << setw(MAX_DECIMAL) << totalDepositos << endl;
                // Información de saldo final
                reporte << left << setw(MAX_CABECERA) << "SALDO FINAL: " << right;
                reporte << moneda << setw(MAX_DECIMAL) << saldoFinal << endl;
            }
            separacion(reporte, '=', MAX_LINEA);
        }
    }
    return 0;
}

