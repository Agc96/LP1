/*
 * Archivo: AsignacionDinamicaMemoriaPorIncrementos.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   22 de septiembre de 2023, 12:48 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "AsignacionDinamicaMemoriaPorIncrementos.h"
using namespace std;

#define INCREMENTO 5
#define MAX_BUFFER 200
#define LINEA_REP_PRODUCTOS 85
#define LINEA_REP_PEDIDOS 32
#define LINEA_REP_ENTREGA 117
#define NO_ENCONTRADO -1

/* Pregunta 1 */

void lecturaDeProductos(const char *nomArch, char ***&arrProductos,
        int *&arrStock, double *&arrPrecios) {
    ifstream arch;
    abrirArchivoEntrada(arch, nomArch);
    char **producto, *codProd, *descProd, coma;
    int stock, numDatos = 0, capDatos = 0;
    double precio;
    while (true) {
        codProd = leerCadena(arch);
        if (codProd == nullptr) break;
        descProd = leerCadena(arch);
        arch >> precio >> coma >> stock >> ws;
        // Incrementar espacios de ser necesario
        if (numDatos == capDatos)
            incrementarEspaciosProductos(arrProductos, arrStock, arrPrecios,
                    numDatos, capDatos);
        // Guardar datos en los arreglos
        producto = new char*[2];
        producto[0] = codProd;
        producto[1] = descProd;
        arrProductos[numDatos-1] = producto;
        arrStock[numDatos-1] = stock;
        arrPrecios[numDatos-1] = precio;
        numDatos++;
    }
}

void incrementarEspaciosProductos(char ***&productos, int *&stock,
        double *&precios, int &numDatos, int &capDatos) {
    char ***auxProductos;
    int *auxStock;
    double *auxPrecios;
    capDatos += INCREMENTO;
    if (numDatos == 0) {
        productos = new char**[capDatos]{};
        stock = new int[capDatos]{};
        precios = new double[capDatos]{};
        numDatos = 1;
    } else {
        auxProductos = new char**[capDatos]{};
        auxStock = new int[capDatos]{};
        auxPrecios = new double[capDatos]{};
        for (int i = 0; i < numDatos; i++) {
            auxProductos[i] = productos[i];
            auxStock[i] = stock[i];
            auxPrecios[i] = precios[i];
        }
        delete[] productos;
        delete[] stock;
        delete[] precios;
        productos = auxProductos;
        stock = auxStock;
        precios = auxPrecios;
    }
}

void pruebaDeLecturaDeProductos(const char *nomArch, char ***arrProductos,
        int *arrStock, double *arrPrecios) {
    ofstream arch;
    crearArchivoSalida(arch, nomArch);
    char **producto;
    // Imprimir cabecera
    arch << fixed << setprecision(2);
    arch << left << setw(10) << "Codigo" << setw(60) << "Descripcion"
            << setw(8) << "Stock" << "Precio" << endl;
    imprimirLinea(arch, '=', LINEA_REP_PRODUCTOS);
    // Imprimir listado de productos
    for (int i = 0; arrProductos[i]; i++) {
        producto = arrProductos[i];
        arch << left << setw(10) << producto[0] << setw(60) << producto[1];
        arch << right << setw(5) << arrStock[i] << setw(10) << arrPrecios[i];
        arch << endl;
    }
}

/* Pregunta 2 */

void lecturaDePedidos(const char *nomArch, int *&arrFechaPedidos,
        char ***&arrCodigoPedidos, int ***&arrDniCantPedidos) {
    ifstream arch;
    abrirArchivoEntrada(arch, nomArch);
    char *codProd, car;
    int dni, cant, dd, mm, aaaa, fecha, posFecha, *arrNumPedidos, *arrCapPedidos,
            numFechas = 0, capFechas = 0;
    while (true) {
        codProd = leerCadena(arch);
        if (codProd == nullptr) break;
        arch >> dni >> car >> cant >> car >> dd >> car >> mm >> car >> aaaa >> ws;
        fecha = 10000*aaaa + 100*mm + dd;
        // Buscar fecha en el arreglo
        posFecha = buscarFecha(arrFechaPedidos, numFechas, fecha);
        if (posFecha == NO_ENCONTRADO) {
            if (numFechas == capFechas)
                incrementarEspaciosFechas(arrFechaPedidos, arrCodigoPedidos,
                        arrDniCantPedidos, arrNumPedidos, arrCapPedidos,
                        numFechas, capFechas);
            posFecha = agregarFechaOrdenada(arrFechaPedidos, arrCodigoPedidos,
                    arrDniCantPedidos, arrNumPedidos, arrCapPedidos, numFechas,
                    fecha);
            numFechas++;
        }
        agregarPedido(codProd, dni, cant, arrCodigoPedidos[posFecha],
                arrDniCantPedidos[posFecha], arrNumPedidos[posFecha],
                arrCapPedidos[posFecha]);
    }
}

int agregarFechaOrdenada(int *arrFechaPedidos, char ***arrCodigoPedidos,
        int ***arrDniCantPedidos, int *arrNumPedidos, int *arrCapPedidos,
        int numFechas, int nuevaFecha) {
    int i;
    for (i = numFechas - 1; i > 0; i--) {
        if (arrFechaPedidos[i-1] > nuevaFecha) {
            arrFechaPedidos[i] = arrFechaPedidos[i-1];
            arrCodigoPedidos[i] = arrCodigoPedidos[i-1];
            arrDniCantPedidos[i] = arrDniCantPedidos[i-1];
            arrNumPedidos[i] = arrNumPedidos[i-1];
            arrCapPedidos[i] = arrCapPedidos[i-1];
        }
        else break;
    }
    arrFechaPedidos[i] = nuevaFecha;
    arrNumPedidos[i] = arrCapPedidos[i] = 0;
    return i;
}

int buscarFecha(int *arrFechaPedidos, int numFechas, int fechaBuscada) {
    for (int i = 0; i < numFechas-1; i++) {
        if (arrFechaPedidos[i] == fechaBuscada)
            return i;
    }
    return NO_ENCONTRADO;
}

void incrementarEspaciosFechas(int *&fechaPedidos, char ***&codigoPedidos,
        int ***&dniCantPedidos, int *&numPedidos, int *&capPedidos,
        int &numFechas, int &capFechas) {
    char ***auxCodigoPedidos;
    int *auxFechaPedidos, ***auxDniCantPedidos, *auxNumPedidos, *auxCapPedidos;
    capFechas += INCREMENTO;
    if (numFechas == 0) {
        fechaPedidos = new int[capFechas]{};
        codigoPedidos = new char **[capFechas]{};
        dniCantPedidos = new int **[capFechas]{};
        numPedidos = new int[capFechas]{};
        capPedidos = new int[capFechas]{};
        numFechas = 1;
    } else {
        auxFechaPedidos = new int[capFechas]{};
        auxCodigoPedidos = new char **[capFechas]{};
        auxDniCantPedidos = new int **[capFechas]{};
        auxNumPedidos = new int[capFechas]{};
        auxCapPedidos = new int[capFechas]{};
        for (int i = 0; i < numFechas; i++) {
            auxFechaPedidos[i] = fechaPedidos[i];
            auxCodigoPedidos[i] = codigoPedidos[i];
            auxDniCantPedidos[i] = dniCantPedidos[i];
            auxNumPedidos[i] = numPedidos[i];
            auxCapPedidos[i] = capPedidos[i];
        }
        delete[] fechaPedidos;
        delete[] codigoPedidos;
        delete[] dniCantPedidos;
        delete[] numPedidos;
        delete[] capPedidos;
        fechaPedidos = auxFechaPedidos;
        codigoPedidos = auxCodigoPedidos;
        dniCantPedidos = auxDniCantPedidos;
        numPedidos = auxNumPedidos;
        capPedidos = auxCapPedidos;
    }
}

void agregarPedido(char *codProd, int dni, int cantidad, char **&arrCodigoPedido,
        int **&arrDniCantPedido, int &numPedidos, int &capPedidos) {
    char **auxCodigoPedido;
    int *auxPedido, **auxDniCantPedido;
    // Incrementar espacios de ser necesario
    if (numPedidos == capPedidos) {
        capPedidos += INCREMENTO;
        if (numPedidos == 0) {
            arrCodigoPedido = new char *[capPedidos]{};
            arrDniCantPedido = new int *[capPedidos]{};
            numPedidos = 1;
        } else {
            auxCodigoPedido = new char *[capPedidos]{};
            auxDniCantPedido = new int *[capPedidos]{};
            for (int i = 0; i < numPedidos; i++) {
                auxCodigoPedido[i] = arrCodigoPedido[i];
                auxDniCantPedido[i] = arrDniCantPedido[i];
            }
            delete[] arrCodigoPedido;
            delete[] arrDniCantPedido;
            arrCodigoPedido = auxCodigoPedido;
            arrDniCantPedido = auxDniCantPedido;
        }
    }
    // Agregar datos al final del arreglo
    auxPedido = new int[2];
    auxPedido[0] = dni;
    auxPedido[1] = cantidad;
    arrCodigoPedido[numPedidos-1] = codProd;
    arrDniCantPedido[numPedidos-1] = auxPedido;
    numPedidos++;
}

void pruebaDeLecturaDePedidos(const char *nomArch, int *fechaPedidos,
        char ***codigoPedidos, int ***dniCantPedidos) {
    ofstream arch;
    crearArchivoSalida(arch, nomArch);
    char **auxCodigoPedidos;
    int *auxPedido, **auxDniCantPedidos;
    arch << fixed << setprecision(2);
    for (int i = 0; fechaPedidos[i]; i++) {
        // Imprimir cabecera
        imprimirLinea(arch, '=', LINEA_REP_PEDIDOS);
        imprimirFecha(arch, fechaPedidos[i]);
        imprimirLinea(arch, '-', LINEA_REP_PEDIDOS);
        arch << left << setw(12) << "Producto" << setw(12) << "DNI"
                << "Cantidad" << endl;
        // Imprimir listado
        auxCodigoPedidos = codigoPedidos[i];
        auxDniCantPedidos = dniCantPedidos[i];
        for (int j = 0; auxCodigoPedidos[j]; j++) {
            arch << left << setw(10) << auxCodigoPedidos[j];
            auxPedido = auxDniCantPedidos[j];
            arch << right << setw(10) << auxPedido[0] << setw(12)
                    << auxPedido[1] << endl;
        }
    }
    imprimirLinea(arch, '=', LINEA_REP_PEDIDOS);
}

/* Pregunta 3 */

void reporteDeEntregaDePedidos(const char *nomArch, char ***productos,
        int *stock, double *precios, int *fechaPedidos, char ***codigoPedidos,
        int ***dniCantPedidos) {
    ofstream arch;
    crearArchivoSalida(arch, nomArch);
    double ingresadoFecha, perdidoFecha, ingresadoTotal = 0, perdidoTotal = 0;
    arch << fixed << setprecision(2);
    // Imprimir cabecera del reporte
    arch << "REPORTE DE ENTREGA DE PEDIDOS" << endl;
    imprimirLinea(arch, '=', LINEA_REP_ENTREGA);
    // Imprimir listado de fechas
    for (int i = 0; fechaPedidos[i]; i++) {
        // Imprimir cabecera
        imprimirFecha(arch, fechaPedidos[i]);
        imprimirLinea(arch, '=', LINEA_REP_ENTREGA);
        arch << left << setw(5) << "No." << setw(10) << "DNI" << setw(65)
                << "Producto" << setw(10) << "Cantidad" << setw(10) << "Precio"
                << "Total de ingresos" << endl;
        imprimirLinea(arch, '-', LINEA_REP_ENTREGA);
        // Imprimir listado
        imprimirListaPedidos(arch, productos, stock, precios, codigoPedidos[i],
                dniCantPedidos[i], ingresadoFecha, perdidoFecha);
        imprimirLinea(arch, '-', LINEA_REP_ENTREGA);
        arch << right << "Total ingresado: " << setw(27) << ingresadoFecha << endl;
        arch << "Total perdido por falta de stock: " << setw(10) << perdidoFecha << endl;
        ingresadoTotal += ingresadoFecha;
        perdidoTotal += perdidoFecha;
        imprimirLinea(arch, '=', LINEA_REP_ENTREGA);
    }
    // Imprimir resumen del reporte
    arch << "Resumen de ingresos:" << endl;
    arch << "Total de ingresos en el periodo: " << setw(11) << ingresadoTotal << endl;
    arch << "Total perdido por falta de stock: " << setw(10) << perdidoTotal << endl;
    imprimirLinea(arch, '=', LINEA_REP_ENTREGA);
}

void imprimirListaPedidos(ofstream &arch, char ***productos, int *stock,
        double *precios, char **codigoPedido, int **dniCantPedido,
        double &totalIngresado, double &totalPerdido) {
    char **auxProd;
    int *auxPedido, posProd;
    double monto;
    totalIngresado = totalPerdido = 0;
    for (int j = 0; codigoPedido[j]; j++) {
        // Buscar datos del producto
        posProd = buscarProducto(productos, codigoPedido[j]);
        if (posProd == NO_ENCONTRADO) continue;
        // Realizar los cálculos e impresiones necesarias
        auxProd = productos[posProd];
        auxPedido = dniCantPedido[j];
        arch << right << setw(2) << (j+1) << left << setw(3) << ')' << setw(10)
                << auxPedido[0] << setw(9) << auxProd[0] << setw(56)
                << auxProd[1] << right << setw(5) << auxPedido[1] << setw(13)
                << precios[posProd];
        monto = precios[posProd] * auxPedido[1];
        if (stock[posProd] >= auxPedido[1]) {
            stock[posProd] -= auxPedido[1];
            totalIngresado += monto;
            arch << setw(15) << monto << endl;
        } else {
            totalPerdido += monto;
            arch << setw(15) << "SIN STOCK" << endl;
        }
    }
}

int buscarProducto(char ***productos, char *codProdBuscado) {
    char **auxProd;
    for (int k = 0; productos[k]; k++) {
        auxProd = productos[k];
        if (strcmp(auxProd[0], codProdBuscado) == 0)
            return k;
    }
    return NO_ENCONTRADO;
}

/* Funciones auxiliares */

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void crearArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
}

char *leerCadena(ifstream &arch, char delim) {
    char buffer[MAX_BUFFER], *cadena;
    arch.getline(buffer, MAX_BUFFER, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void imprimirFecha(ofstream &arch, int fecha) {
    int dd, mm, aaaa;
    dd = fecha % 100;
    mm = (fecha / 100) % 100;
    aaaa = fecha / 10000;
    arch << "FECHA: " << setfill('0') << setw(2) << dd << '/' << setw(2)
            << mm << '/' << aaaa << setfill(' ') << endl;
}

void imprimirLinea(ofstream &arch, char car, int cant) {
    for (int i = 0; i < cant; i++)
        arch.put(car);
    arch << endl;
}
