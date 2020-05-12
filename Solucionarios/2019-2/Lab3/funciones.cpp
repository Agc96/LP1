/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 20 de septiembre de 2019, 10:45 AM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "constantes.h"
#include "funciones.h"
#include "utilidades.h"
using namespace std;

void generarRegistroBinario(ifstream& regTexto) {
    // Generar archivo binario de registros
    ofstream regBinario("files/registro.bin", ios::out | ios::binary);
    if (!regBinario) {
        cout << "No se pudo generar el registro de ventas binario." << endl;
        exit(1);
    }
    // Declarar variables
    int cliente, fecha, numDoc, referencia;
    double monto;
    char tipoDoc;
    // Leer detalles de venta
    while (regTexto >> cliente) {
        obtenerDetallesVenta(regTexto, fecha, tipoDoc, numDoc, monto, referencia);
        // Escribir datos en el archivo binario
        regBinario.write(reinterpret_cast<const char*>(&cliente), sizeof(int));
        regBinario.write(reinterpret_cast<const char*>(&fecha), sizeof(int));
        regBinario.write(reinterpret_cast<const char*>(&tipoDoc), sizeof(char));
        regBinario.write(reinterpret_cast<const char*>(&numDoc), sizeof(int));
        regBinario.write(reinterpret_cast<const char*>(&monto), sizeof(double));
        regBinario.write(reinterpret_cast<const char*>(&referencia), sizeof(int));
    }
}

void obtenerDetallesVenta(ifstream& regTexto, int& fecha, char& tipoDocumento,
        int& numDocumento, double& monto, int& referencia) {
    // Declaración de variables
    int dia, mes, anho, serie, secuencia;
    char c;
    // Leer fecha de venta
    regTexto >> dia >> c >> mes >> c >> anho;
    fecha = 10000*anho + 100*mes + dia;
    // Leer tipo de documento
    regTexto >> tipoDocumento;
    while (regTexto.get() != ' ');
    // Leer número de documento
    regTexto >> serie >> c >> secuencia;
    numDocumento = 100000*serie + secuencia;
    // Leer monto de venta y referencia
    regTexto >> monto >> referencia;
}

void actualizarMontos(ifstream& devoluciones, ifstream& precios) {
    // Editar archivo binario de registros
    fstream registro("files/registro.bin", ios::in | ios::out | ios::binary);
    if (!registro) {
        cout << "No se pudo editar el registro de ventas binario." << endl;
        exit(1);
    }
    // Declaración de variables
    int ultimoCodigo = 0, codigo, dia, mes, anho, fecha, producto, cantidad;
    double precio, montoTotal;
    char c;
    // Leer datos de devoluciones
    while (devoluciones >> codigo) {
        if (ultimoCodigo != codigo) {
            // Actualizar el registro de ventas
            if (ultimoCodigo != 0) {
                actualizarRegistroVentas(registro, ultimoCodigo, montoTotal);
            }
            // Inicializar valores
            montoTotal = 0;
            ultimoCodigo = codigo;
        }
        // Leer fecha de devolución
        devoluciones >> dia >> c >> mes >> c >> anho;
        fecha = 10000 * anho + 100 * mes + dia;
        // Leer código de producto y cantidad
        devoluciones >> producto >> cantidad;
        // Buscar el precio del producto en el mes
        precio = buscarPrecioProducto(precios, mes, anho, producto);
        montoTotal += (precio * cantidad);
    }
    actualizarRegistroVentas(registro, ultimoCodigo, montoTotal);
}

double buscarPrecioProducto(ifstream& precios, int mesBuscado, int anhoBuscado,
        int productoBuscado) {
    int mesLeido, anhoLeido, productoLeido;
    double precioUnitario;
    char c;
    // Ir al inicio del archivo
    precios.seekg(0, ios::beg);
    while (precios >> productoLeido) {
        c = precios.get();
        // Leer año en caso de encontrar un punto
        if (c == '.') {
            mesLeido = productoLeido;
            precios >> anhoLeido;
        }
        // Leer precio unitario en caso de encontrar un espacio
        else if (c == ' ') {
            precios >> precioUnitario;
            // Verificar que es el precio que queremos
            if (mesBuscado == mesLeido && anhoBuscado == anhoLeido &&
                    productoBuscado == productoLeido) {
                return precioUnitario;
            }
        }
    }
    // Si no se encontró el precio, mostrar mensaje de error
    cout << "No se encontró el precio para el producto " << productoBuscado
            << " en el periodo " << mesBuscado << '/' << anhoBuscado << endl;
    exit(1);
}

void actualizarRegistroVentas(fstream& registro, int referenciaBuscada, double monto) {
    // Declaración de variables
    int tamRegistro, numRegistros, referenciaLeida;
    // Obtener la cantidad de registros de ventas
    tamRegistro = 4*sizeof(int) + sizeof(char) + sizeof(double);
    registro.seekg(0, ios::end);
    numRegistros = registro.tellg() / tamRegistro;
    // Buscar el registro con la referencia buscada
    for (int i = 1; i <= numRegistros; i++) {
        registro.seekg(tamRegistro*i - sizeof(int), ios::beg);
        registro.read(reinterpret_cast<char*>(&referenciaLeida), sizeof(int));
        if (referenciaBuscada == referenciaLeida) {
            // Reemplazar el monto de devolución
            registro.seekg(tamRegistro*i - sizeof(int) - sizeof(double), ios::beg);
            registro.write(reinterpret_cast<const char*>(&monto), sizeof(double));
            return;
        }
    }
    // Si no se encontró la referencia, mostrar mensaje de error
    cout << "No se pudo encontrar la referencia " << referenciaBuscada
            << " en el registro de ventas." << endl;
    exit(1);
}

void generarReporte(ofstream& reporte) {
    // Abrir archivo binario de registros
    ifstream registro("files/registro.bin", ios::in | ios::binary);
    if (!registro) {
        cout << "No se pudo abrir el registro de ventas binario." << endl;
        exit(1);
    }
    // Declaración de variables
    int fecha, cliente, numDoc, referencia, tamRegistro, numRegistros;
    double monto, saldoFinal = 0;
    char tipoDoc;
    // Escribir cabecera
    escribirCabeceraReporte(reporte);
    // Obtener la cantidad de registros de ventas
    tamRegistro = 4*sizeof(int) + sizeof(char) + sizeof(double);
    registro.seekg(0, ios::end);
    numRegistros = registro.tellg() / tamRegistro;
    // Leer cada detalle de venta
    for (int i = 0; i < numRegistros; i++) {
        registro.seekg(tamRegistro*i, ios::beg);
        registro.read(reinterpret_cast<char*>(&cliente), sizeof(int));
        registro.read(reinterpret_cast<char*>(&fecha), sizeof(int));
        registro.read(reinterpret_cast<char*>(&tipoDoc), sizeof(char));
        registro.read(reinterpret_cast<char*>(&numDoc), sizeof(int));
        registro.read(reinterpret_cast<char*>(&monto), sizeof(double));
        registro.read(reinterpret_cast<char*>(&referencia), sizeof(int));
        // Escribir datos del detalle de venta
        escribirDetallesVenta(reporte, cliente, fecha, tipoDoc, numDoc, monto,
                referencia, saldoFinal);
    }
    // Escribir resumen
    escribirResumenReporte(reporte, saldoFinal);
}

void escribirCabeceraReporte(ofstream& reporte) {
    reporte << left << fixed << setprecision(MAX_PRECISION)
            << "REGISTRO DE VENTAS" << endl;
    separacion(reporte, '=');
    reporte << setw(MAX_FECHA) << "FECHA"
            << setw(MAX_CLIENTE) << "CLIENTE"
            << setw(MAX_TIPO) << "TIPO"
            << setw(MAX_SERIE) << "DOCUMENTO"
            << setw(MAX_MONTO) << "MONTO"
            << setw(MAX_MONTO) << "IGV"
            << setw(MAX_MONTO) << "MONTO TOTAL"
            << setw(MAX_REFERENCIA) << "REFERENCIA" << endl;
    separacion(reporte, '-');
}

void escribirDetallesVenta(ofstream& reporte, int cliente, int fecha,
        char tipoDocumento, int numDocumento, double monto, int referencia,
        double& saldoFinal) {
    // Calcular subtotales
    double montoIgv = monto * IGV;
    double montoTotal = monto + montoIgv;
    // Escribir fecha
    reporte << right << setfill('0')
            << setw(2) << (fecha % 100) << '/'
            << setw(2) << ((fecha / 100) % 100) << '/'
            << setw(4) << (fecha / 10000) << setfill(' ');
    espacios(reporte, MAX_FECHA - 10);
    // Escribir código del cliente
    reporte << left << setw(MAX_CLIENTE) << cliente;
    // Escribir tipo de documento y actualizar saldo final
    if (tipoDocumento == 'F') {
        reporte << left << setw(MAX_TIPO) << "FAC";
        saldoFinal += montoTotal;
    } else {
        reporte << left << setw(MAX_TIPO) << "N/C";
        saldoFinal -= montoTotal;
    }
    // Escribir número de documento
    reporte << right << setfill('0')
            << setw(4) << (numDocumento / 100000) << '-'
            << setw(5) << (numDocumento % 100000) << setfill(' ');
    espacios(reporte, MAX_SERIE - 10);
    // Escribir montos
    reporte << setw(MAX_DECIMAL) << monto;
    espacios(reporte, MAX_MONTO - MAX_DECIMAL);
    reporte << setw(MAX_DECIMAL) << montoIgv;
    espacios(reporte, MAX_MONTO - MAX_DECIMAL);
    reporte << setw(MAX_DECIMAL) << montoTotal;
    espacios(reporte, MAX_MONTO - MAX_DECIMAL);
    // Escribir referencia
    reporte << setw(MAX_REFERENCIA) << referencia << endl;
}

void escribirResumenReporte(ofstream& reporte, double saldoFinal) {
    separacion(reporte, '=');
    reporte << "RESUMEN:" << endl;
    reporte << "SALDO FINAL:" << setw(MAX_MONTO) << saldoFinal << endl;
}
