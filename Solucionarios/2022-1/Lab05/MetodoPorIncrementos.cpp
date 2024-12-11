/*
 * Archivo: MetodoPorIncrementos.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   13 de mayo de 2022, 08:12 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "MetodoPorIncrementos.h"
using namespace std;

#define MAX_COD_PROD 10
#define MAX_DESCRIP 45
#define MAX_LINEA_REPORTE1 80
#define MAX_LINEA_REPORTE2 130
#define INCREMENTO 5
#define NO_ENCONTRADO -1

void CargaDePedidosYProductos(int **cli_DniTelefono, char ***&pro_CodigoDescripcion,
        double **&pro_PrecioDescuento, char ***&ped_Codigo, int ***&ped_FechaCantidad,
        const char *nomArch) {
    ifstream arch;
    char codProd[MAX_COD_PROD], descrip[MAX_DESCRIP];
    int cantidad, dni, fecha, indCli, numProd = 0, capProd = 0, *numPed, *capPed;
    double descuento, precUnit;
    // Leer línea por línea
    AbrirArchivoLectura(arch, nomArch);
    InicializarArrPedidos(cli_DniTelefono, ped_Codigo, ped_FechaCantidad, numPed, capPed);
    while (true) {
        LeerPedido(arch, codProd, descrip, cantidad, descuento, precUnit, dni, fecha);
        // Buscar si el producto existe y agregar los datos correspondientes
        if (numProd == 0 || BuscarProducto(pro_CodigoDescripcion, codProd) == NO_ENCONTRADO) {
            AgregarProducto(pro_CodigoDescripcion, pro_PrecioDescuento, numProd, capProd,
                    codProd, descrip, precUnit, descuento);
        }
        // Buscar índice del cliente y agregar los datos correspondientes
        indCli = BuscarCliente(cli_DniTelefono, dni);
        if (indCli != NO_ENCONTRADO) {
            AgregarPedido(ped_Codigo, ped_FechaCantidad, numPed, capPed, indCli,
                    codProd, fecha, cantidad);
        }
        if (arch.eof()) break;
    }
    // Eliminar arreglos que ya no necesitaremos
    delete numPed;
    delete capPed;
}

void InicializarArrPedidos(int **cli_DniTelefono, char ***&ped_Codigo,
        int ***&ped_FechaCantidad, int *&numPed, int *&capPed) {
    int numCli;
    // Obtener la cantidad de elementos
    for (numCli = 0; cli_DniTelefono[numCli]; numCli++);
    // Asignar espacios de memoria
    ped_Codigo = new char**[numCli+1];
    ped_FechaCantidad = new int**[numCli+1];
    numPed = new int[numCli+1];
    capPed = new int[numCli+1];
    // Inicializar espacios
    for (int i = 0; i <= numCli; i++) {
        ped_Codigo[i] = nullptr;
        ped_FechaCantidad[i] = nullptr;
        numPed[i] = 0;
        capPed[i] = 0;
    }
}

void LeerPedido(ifstream &arch, char *codProd, char *descrip, int &cantProd,
        double &descuento, double &precUnit, int &dni, int &fecha) {
    int dd, mm, aaaa;
    char c;
    // Leer los datos de la línea del pedido
    arch.getline(codProd, MAX_COD_PROD, ',');
    arch.getline(descrip, MAX_DESCRIP, ',');
    arch >> cantProd;
    if (arch.fail()) {
        arch.clear();
        arch >> c >> descuento >> c >> cantProd;
    } else {
        descuento = 0;
    }
    arch >> c >> precUnit >> c >> dni >> c >> dd >> c >> mm >> c >> aaaa >> ws;
    fecha = 10000*aaaa + 100*mm + dd;
}

int BuscarProducto(char ***pro_CodigoDescripcion, char *codProd) {
    for (int i = 0; pro_CodigoDescripcion[i]; i++) {
        if (strcmp(pro_CodigoDescripcion[i][0], codProd) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void AgregarProducto(char ***&pro_CodigoDescripcion, double **&pro_PrecioDescuento, int &numProd,
        int &capProd, char *codProd, char *descrip, double precUnit, double descuento) {
    char **codDesc;
    double *precDesc;
    // Verificar si se deben incrementar los espacios
    if (numProd == 0 || (numProd+1) == capProd) {
        IncrementarProductos(pro_CodigoDescripcion, pro_PrecioDescuento, numProd, capProd);
    }
    // Crear arreglos secundarios
    codDesc = new char*[2];
    codDesc[0] = CrearCadenaExacta(codProd);
    codDesc[1] = CrearCadenaExacta(descrip);
    precDesc = new double[2];
    precDesc[0] = precUnit;
    precDesc[1] = descuento;
    // Actualizar arreglos de productos
    pro_CodigoDescripcion[numProd] = codDesc;
    pro_PrecioDescuento[numProd] = precDesc;
    numProd++;
    pro_CodigoDescripcion[numProd] = nullptr;
    pro_PrecioDescuento[numProd] = nullptr;
}

void IncrementarProductos(char ***&pro_CodigoDescripcion, double **&pro_PrecioDescuento,
        int numProd, int &capProd) {
    char ***auxCodDescrip;
    double **auxPrecioDesc;
    // Actualizar contadores y crear nuevos espacios de memoria
    capProd += INCREMENTO;
    auxCodDescrip = new char**[capProd];
    auxPrecioDesc = new double*[capProd];
    // Para el segundo incremento en adelante, copiar los datos y eliminar
    if (numProd) {
        for (int i = 0; i < numProd; i++) {
            auxCodDescrip[i] = pro_CodigoDescripcion[i];
            auxPrecioDesc[i] = pro_PrecioDescuento[i];
        }
        delete pro_CodigoDescripcion;
        delete pro_PrecioDescuento;
    }
    // Asignar los nuevos espacios de memoria en los punteros correspondientes
    pro_CodigoDescripcion = auxCodDescrip;
    pro_PrecioDescuento = auxPrecioDesc;
}

int BuscarCliente(int **cli_DniTelefono, int dni) {
    for (int i = 0; cli_DniTelefono[i]; i++) {
        if (cli_DniTelefono[i][0] == dni) return i;
    }
    return NO_ENCONTRADO;
}

void AgregarPedido(char ***ped_Codigo, int ***ped_FechaCantidad, int *numPed,
        int *capPed, int indCli, char *codProd, int fecha, int cantidad) {
    int *fechaCant;
    // Verificar si se deben incrementar los espacios
    if (numPed[indCli] == 0 || (numPed[indCli]+1) == capPed[indCli]) {
        IncrementarPedidos(ped_Codigo, ped_FechaCantidad, numPed, capPed, indCli);
    }
    // Crear arreglos secundarios
    fechaCant = new int[2];
    fechaCant[0] = fecha;
    fechaCant[1] = cantidad;
    // Actualizar arreglos de productos
    ped_Codigo[indCli][numPed[indCli]] = CrearCadenaExacta(codProd);
    ped_FechaCantidad[indCli][numPed[indCli]] = fechaCant;
    numPed[indCli]++;
    ped_Codigo[indCli][numPed[indCli]] = nullptr;
    ped_FechaCantidad[indCli][numPed[indCli]] = nullptr;
}

void IncrementarPedidos(char ***ped_Codigo, int ***ped_FechaCantidad, int *numPed,
        int *capPed, int indCli) {
    char **auxCodigo;
    int **auxFechaCant;
    // Actualizar contadores y crear nuevos espacios de memoria
    capPed[indCli] += INCREMENTO;
    auxCodigo = new char*[capPed[indCli]];
    auxFechaCant = new int*[capPed[indCli]];
    // Para el segundo incremento en adelante, copiar los datos y eliminar
    if (numPed[indCli]) {
        for (int i = 0; i < numPed[indCli]; i++) {
            auxCodigo[i] = ped_Codigo[indCli][i];
            auxFechaCant[i] = ped_FechaCantidad[indCli][i];
        }
        delete ped_Codigo[indCli];
        delete ped_FechaCantidad[indCli];
    }
    // Asignar los nuevos espacios de memoria en los punteros correspondientes
    ped_Codigo[indCli] = auxCodigo;
    ped_FechaCantidad[indCli] = auxFechaCant;
}

void ReporteDePedidosYProductos(int **cli_DniTelefono, char ***pro_CodigoDescripcion,
        double **pro_PrecioDescuento, char ***ped_Codigo, int ***ped_FechaCantidad,
        const char *nomArch) {
    ofstream arch;
    AbrirArchivoEscritura(arch, nomArch);
    arch << fixed << setprecision(2);
    // Imprimir cabecera de productos
    arch << "LISTADO DE PRODUCTOS" << endl;
    ImprimirLinea(arch, '=', MAX_LINEA_REPORTE1);
    arch << left << setw(MAX_COD_PROD) << "CODIGO" << setw(MAX_DESCRIP) << "DESCRIPCION"
            << right << setw(10) << "PRECIO" << setw(15) << "DESCUENTO" << endl;
    // Imprimir listado de productos
    for (int i = 0; pro_CodigoDescripcion[i]; i++) {
        arch << left << setw(MAX_COD_PROD) << pro_CodigoDescripcion[i][0]
                << setw(MAX_DESCRIP) << pro_CodigoDescripcion[i][1]
                << right << setw(10) << pro_PrecioDescuento[i][0]
                << setw(15) << pro_PrecioDescuento[i][1] << endl;
    }
    // Imprimir cabecera de pedidos
    arch << endl << "LISTADO DE PEDIDOS" << endl;
    ImprimirLinea(arch, '=', MAX_LINEA_REPORTE1);
    arch << left << setw(15) << "DNI" << setw(15) << "CODIGO"
            << setw(15) << "FECHA" << "CANTIDAD" << endl;
    // Imprimir listado de pedidos
    for (int i = 0; cli_DniTelefono[i]; i++) {
        for (int j = 0; ped_Codigo[i][j]; j++) {
            arch << left << setw(15) << cli_DniTelefono[i][0]
                    << setw(15) << ped_Codigo[i][j];
            ImprimirFecha(arch, ped_FechaCantidad[i][j][0]);
            arch << right << setw(13) << ped_FechaCantidad[i][j][1] << endl;
        }
    }
}

void ReporteRelacionDePedidos(int **cli_DniTelefono, char ***cli_NombreCategoria,
        char ***pro_CodigoDescripcion, double **pro_PrecioDescuento, char ***ped_Codigo,
        int ***ped_FechaCantidad, const char *nomArch) {
    ofstream arch;
    int indProd;
    double totalAPagar, totalDesc;
    // Imprimir cabecera del reporte
    AbrirArchivoEscritura(arch, nomArch);
    arch << fixed << setprecision(2);
    arch << setw(83) << "EMPRESA COMERCIALIZADORA DE ABARROTES" << endl;
    ImprimirLinea(arch, '=', MAX_LINEA_REPORTE2);
    arch << "GASTOS DE LOS CLIENTES REGISTRADOS:" << endl;
    // Imprimir listado de clientes
    for (int i = 0; cli_DniTelefono[i]; i++) {
        ImprimirCabeceraClientes(arch, cli_DniTelefono, cli_NombreCategoria, i);
        totalAPagar = totalDesc = 0;
        for (int j = 0; ped_Codigo[i][j]; j++) {
            // Buscar el índice del producto
            indProd = BuscarProducto(pro_CodigoDescripcion, ped_Codigo[i][j]);
            if (indProd != NO_ENCONTRADO) {
                ImprimirPedido(arch, pro_CodigoDescripcion, pro_PrecioDescuento,
                        ped_FechaCantidad, indProd, i, j, totalAPagar, totalDesc);
            }
        }
        ImprimirLinea(arch, '-', MAX_LINEA_REPORTE2);
        arch << setw(93) << "TOTAL:" << setw(12) << totalAPagar
                << setw(9) << totalDesc << endl;
        ImprimirLinea(arch, '=', MAX_LINEA_REPORTE2);
        arch << endl;
    }
}

void ImprimirCabeceraClientes(ofstream &arch, int **cli_DniTelefono,
        char ***cli_NombreCategoria, int indCli) {
    // Imprimir datos del cliente
    ImprimirLinea(arch, '=', MAX_LINEA_REPORTE2);
    arch << left << setw(12) << "DNI" << setw(50) << "Nombre"
            << setw(17) << "Categoria" << "Telefono" << endl;
    arch << setw(12) << cli_DniTelefono[indCli][0]
            << setw(50) << cli_NombreCategoria[indCli][0]
            << right << setw(5) << *cli_NombreCategoria[indCli][1]
            << setw(20) << cli_DniTelefono[indCli][1] << endl;
    // Imprimir cabecera de los productos
    ImprimirLinea(arch, '-', MAX_LINEA_REPORTE2);
    arch << "PRODUCTOS ADQUIRIDOS:" << endl;
    ImprimirLinea(arch, '-', MAX_LINEA_REPORTE2);
    arch << left << setw(4) << ' ' << setw(8) << "Codigo"
            << setw(45) << "Descripcion" << right << setw(5) << "P.U."
            << setw(11) << "Cantidad" << setw(9) << "Total"
            << setw(14) << "Descuento %" << setw(9) << "A Pagar"
            << setw(11) << "Descuento" << setw(9) << "Fecha" << endl;
    ImprimirLinea(arch, '-', MAX_LINEA_REPORTE2);
}

void ImprimirPedido(ofstream &arch, char ***pro_CodigoDescripcion,
        double **pro_PrecioDescuento, int ***ped_FechaCantidad, int indProd,
        int indCli, int indPed, double &totalAPagar, double &totalDesc) {
    double precUnit, porcDesc, total, aPagar, descuento;
    int cantidad;
    // Calcular los datos intermedios
    precUnit = pro_PrecioDescuento[indProd][0];
    porcDesc = pro_PrecioDescuento[indProd][1];
    cantidad = ped_FechaCantidad[indCli][indPed][1];
    total = precUnit * cantidad;
    aPagar = total * (1 - porcDesc/100);
    descuento = total - aPagar;
    totalAPagar += aPagar;
    totalDesc += descuento;
    // Imprimir los datos del pedido
    arch << right << setw(2) << (indPed+1) << setw(2) << ' '
            << left << setw(8) << pro_CodigoDescripcion[indProd][0]
            << setw(45) << pro_CodigoDescripcion[indProd][1]
            << right << setw(6) << precUnit << setw(7) << cantidad
            << setw(13) << total;
    if (porcDesc > 0) {
        arch << setw(10) << porcDesc;
    } else {
        arch << setw(10) << "-.--";
    }
    arch << setw(12) << aPagar << setw(9) << descuento << setw(4) << ' ';
    ImprimirFecha(arch, ped_FechaCantidad[indCli][indPed][0]);
    arch << endl;
}

/* Funciones auxiliares */

void AbrirArchivoLectura(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void AbrirArchivoEscritura(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
}

char *CrearCadenaExacta(char *original) {
    char *cadena = new char[strlen(original)+1];
    strcpy(cadena, original);
    return cadena;
}

void ImprimirLinea(ofstream &arch, char c, int num) {
    for (int i = 0; i < num; i++) {
        arch.put(c);
    }
    arch << endl;
}

void ImprimirFecha(ofstream &arch, int fecha) {
    int dd, mm, aaaa;
    dd = fecha % 100;
    mm = (fecha / 100) % 100;
    aaaa = fecha / 10000;
    arch << right << setfill('0') << setw(2) << dd << '/' << setw(2) << mm << '/'
            << setw(4) << aaaa << setfill(' ');
}
