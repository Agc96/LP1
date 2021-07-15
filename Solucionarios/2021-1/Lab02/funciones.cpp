/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 23 de abril de 2021, 07:50 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
using namespace std;

#define MAX_PLACA 8
#define MAX_NOM_CONDUCTOR 40
#define MAX_NOM_INFRACCION 200
#define MAX_GRAVEDAD 10
#define TAM_REG_CONDUCTORES (MAX_NOM_CONDUCTOR*sizeof(char) + 4*sizeof(int) + 4*sizeof(double))
#define TAM_REG_FALTAS ((MAX_PLACA+MAX_GRAVEDAD)*sizeof(char) + 3*sizeof(int) + sizeof(double))
#define TAM_REG_INFRACCIONES ((MAX_NOM_INFRACCION+MAX_GRAVEDAD)*sizeof(char) + sizeof(int) + sizeof(double))

void transferirConductores() {
    // Apertura de archivos
    ifstream archInfracciones = abrirArchTexto("Infracciones-Conductores.txt");
    ofstream archConductores = crearArchBin("Conductores.bin");
    ofstream archFaltas = crearArchBin("FaltasCometidas.bin");
    // Leer los datos de archivo de conductores
    int dummy, licencia, dd, mm, aaaa, infraccion;
    char placa[MAX_PLACA], nombre[MAX_NOM_CONDUCTOR], c, gravedad;
    while (true) {
        archInfracciones >> dummy;
        if (archInfracciones.eof()) break;
        // Leer datos de la infracción
        if (archInfracciones.fail()) {
            archInfracciones.clear();
            archInfracciones >> placa >> dd >> c >> mm >> c >> aaaa >> ws >> gravedad >> infraccion;
            guardarFalta(archFaltas, placa, licencia, convertirFecha(dd, mm, aaaa), gravedad, infraccion);
        } else {
            // Leer datos del conductor
            licencia = dummy;
            archInfracciones >> ws >> nombre;
            guardarConductor(archConductores, licencia, nombre);
        }
    }
}

void guardarConductor(ofstream& arch, int licencia, char* nombre) {
    int dummyInt = 0;
    double dummyDouble = 0.0;
    arch.write(reinterpret_cast<const char*>(&licencia), sizeof(licencia));
    arch.write(reinterpret_cast<const char*>(nombre), MAX_NOM_CONDUCTOR*sizeof(char));
    arch.write(reinterpret_cast<const char*>(&dummyInt), sizeof(dummyInt));
    arch.write(reinterpret_cast<const char*>(&dummyInt), sizeof(dummyInt));
    arch.write(reinterpret_cast<const char*>(&dummyInt), sizeof(dummyInt));
    arch.write(reinterpret_cast<const char*>(&dummyDouble), sizeof(dummyDouble));
    arch.write(reinterpret_cast<const char*>(&dummyDouble), sizeof(dummyDouble));
    arch.write(reinterpret_cast<const char*>(&dummyDouble), sizeof(dummyDouble));
    arch.write(reinterpret_cast<const char*>(&dummyDouble), sizeof(dummyDouble));
}

void guardarFalta(ofstream& arch, char* placa, int licencia, int fecha, char gravedad, int infraccion) {
    char leve[MAX_GRAVEDAD] = "LEVE", grave[MAX_GRAVEDAD] = "GRAVE", muyGrave[MAX_GRAVEDAD] = "MUY GRAVE";
    double dummy = 0.0;
    arch.write(reinterpret_cast<const char*>(placa), MAX_PLACA*sizeof(char));
    arch.write(reinterpret_cast<const char*>(&licencia), sizeof(licencia));
    arch.write(reinterpret_cast<const char*>(&fecha), sizeof(fecha));
    switch (gravedad) {
        case 'L':
            arch.write(reinterpret_cast<const char*>(leve), sizeof(leve));
            break;
        case 'G':
            arch.write(reinterpret_cast<const char*>(grave), sizeof(grave));
            break;
        case 'M':
            arch.write(reinterpret_cast<const char*>(muyGrave), sizeof(muyGrave));
            break;
    }
    arch.write(reinterpret_cast<const char*>(&infraccion), sizeof(infraccion));
    arch.write(reinterpret_cast<const char*>(&dummy), sizeof(dummy));
}

/* Parte 2 */

void transferirInfracciones() {
    // Apertura de archivos
    ifstream archInfracciones = abrirArchTexto("Infracciones.txt");
    ofstream archBin = crearArchBin("Infracciones.bin");
    // Leer los datos de archivo de infracciones
    char nombre[MAX_NOM_INFRACCION], gravedad[MAX_GRAVEDAD];
    int codigo;
    double monto;
    while (true) {
        archInfracciones >> codigo >> ws >> nombre >> ws >> gravedad >> monto;
        if (archInfracciones.eof()) break;
        archBin.write(reinterpret_cast<const char*>(&codigo), sizeof(codigo));
        archBin.write(reinterpret_cast<const char*>(nombre), sizeof(nombre));
        archBin.write(reinterpret_cast<const char*>(gravedad), sizeof(gravedad));
        archBin.write(reinterpret_cast<const char*>(&monto), sizeof(monto));
    }
}

/* Parte 3 */

void actualizarFaltas() {
    ifstream archInfracciones = abrirArchBin("Infracciones.bin");
    fstream archFaltas = actualizarArchBin("FaltasCometidas.bin");
    // Calcular el número de registros
    int numRegInfracciones = calcularNumRegistros(archInfracciones, TAM_REG_INFRACCIONES);
    int numRegFaltas = calcularNumRegistros(archFaltas, TAM_REG_FALTAS);
    // Leer registro por registro
    int infraccion;
    double monto;
    for (int i = 0; i < numRegFaltas; i++) {
        archFaltas.seekg(TAM_REG_FALTAS*(i+1) - sizeof(int) - sizeof(double), ios::beg);
        archFaltas.read(reinterpret_cast<char*>(&infraccion), sizeof(infraccion));
        monto = buscarMontoInfraccion(archInfracciones, numRegInfracciones, infraccion);
        archFaltas.write(reinterpret_cast<const char*>(&monto), sizeof(monto));
    }
}

double buscarMontoInfraccion(ifstream& arch, int numReg, int infraBuscada) {
    int infraLeida;
    double monto;
    char c;
    for (int i = 0; i < numReg; i++) {
        arch.seekg(TAM_REG_INFRACCIONES*i, ios::beg);
        arch.read(reinterpret_cast<char*>(&infraLeida), sizeof(infraLeida));
        if (infraLeida == infraBuscada) {
            arch.seekg(TAM_REG_INFRACCIONES*(i+1) - sizeof(double), ios::beg);
            arch.read(reinterpret_cast<char*>(&monto), sizeof(monto));
            return monto;
        }
    }
    return 0;
}

void actualizarConductores() {
    ifstream archFaltas = abrirArchBin("FaltasCometidas.bin");
    fstream archConductores = actualizarArchBin("Conductores.bin");
    // Calcular el número de registros
    int numRegFaltas = calcularNumRegistros(archFaltas, TAM_REG_FALTAS);
    int numRegConductores = calcularNumRegistros(archConductores, TAM_REG_CONDUCTORES);
    // Leer registro por registro
    int licencia, numLeves, numGraves, numMuyGraves;
    double montoLeves, montoGraves, montoMuyGraves, montoTotal;
    for (int i = 0; i < numRegConductores; i++) {
        archConductores.seekg(TAM_REG_CONDUCTORES*i, ios::beg);
        archConductores.read(reinterpret_cast<char*>(&licencia), sizeof(licencia));
        calcularMontosConductor(archFaltas, numRegFaltas, licencia, numLeves, numGraves,
                numMuyGraves, montoLeves, montoGraves, montoMuyGraves, montoTotal);
        archConductores.seekg(MAX_NOM_CONDUCTOR*sizeof(char), ios::cur);
        archConductores.write(reinterpret_cast<const char*>(&numLeves), sizeof(numLeves));
        archConductores.write(reinterpret_cast<const char*>(&numGraves), sizeof(numGraves));
        archConductores.write(reinterpret_cast<const char*>(&numMuyGraves), sizeof(numMuyGraves));
        archConductores.write(reinterpret_cast<const char*>(&montoLeves), sizeof(montoLeves));
        archConductores.write(reinterpret_cast<const char*>(&montoGraves), sizeof(montoGraves));
        archConductores.write(reinterpret_cast<const char*>(&montoMuyGraves), sizeof(montoMuyGraves));
        archConductores.write(reinterpret_cast<const char*>(&montoTotal), sizeof(montoTotal));
    }
}

void calcularMontosConductor(ifstream& archFaltas, int numRegFaltas, int licBuscada,
        int& numLeves, int& numGraves, int& numMuyGraves, double& montoLeves,
        double& montoGraves, double& montoMuyGraves, double& montoTotal) {
    // Inicializar contadores
    numLeves = numGraves = numMuyGraves = 0;
    montoLeves = montoGraves = montoMuyGraves = montoTotal = 0;
    // Leer registro por registro
    char gravedad[MAX_GRAVEDAD];
    int licLeida;
    double monto;
    for (int i = 0; i < numRegFaltas; i++) {
        archFaltas.seekg(TAM_REG_FALTAS*i + MAX_PLACA*sizeof(char), ios::beg);
        archFaltas.read(reinterpret_cast<char*>(&licLeida), sizeof(licLeida));
        if (licLeida == licBuscada) {
            archFaltas.seekg(sizeof(int), ios::cur);
            archFaltas.read(reinterpret_cast<char*>(gravedad), sizeof(gravedad));
            archFaltas.seekg(sizeof(int), ios::cur);
            archFaltas.read(reinterpret_cast<char*>(&monto), sizeof(monto));
            actualizarContadores(gravedad[0], monto, numLeves, numGraves, numMuyGraves,
                    montoLeves, montoGraves, montoMuyGraves, montoTotal);
        }
    }
}

void actualizarContadores(char gravedad, double monto, int& numLeves, int& numGraves,
        int& numMuyGraves, double& montoLeves, double& montoGraves, double& montoMuyGraves,
        double& montoTotal) {
    switch (gravedad) {
        case 'L':
            numLeves++;
            montoLeves += monto;
            break;
        case 'G':
            numGraves++;
            montoGraves += monto;
            break;
        case 'M':
            numMuyGraves++;
            montoMuyGraves += monto;
            break;
    }
    montoTotal += monto;
}

/* Parte 4 */

void actualizarFaltasAmnistia() {
    // Apertura de archivos
    ifstream archInfracciones = abrirArchBin("Infracciones.bin");
    fstream archFaltas = actualizarArchBin("FaltasCometidas.bin");
    // Calcular el número de registros
    int numRegInfracciones = calcularNumRegistros(archInfracciones, TAM_REG_INFRACCIONES);
    int numRegFaltas = calcularNumRegistros(archFaltas, TAM_REG_FALTAS);
    // Solicitar una fecha y leer registro por registro
    int fechaLimite = solicitarFecha(), fechaLeida, infraccion;
    char gravedad[MAX_GRAVEDAD];
    double monto;
    for (int i = 0; i < numRegFaltas; i++) {
        archFaltas.seekg(TAM_REG_FALTAS*i + MAX_PLACA*sizeof(char) + sizeof(int), ios::beg);
        archFaltas.read(reinterpret_cast<char*>(&fechaLeida), sizeof(fechaLeida));
        archFaltas.read(reinterpret_cast<char*>(gravedad), sizeof(gravedad));
        archFaltas.read(reinterpret_cast<char*>(&infraccion), sizeof(infraccion));
        monto = buscarMontoInfraccion(archInfracciones, numRegInfracciones, infraccion);
        aplicarDescuentoMonto(fechaLeida, fechaLimite, gravedad[0], monto);
        archFaltas.write(reinterpret_cast<const char*>(&monto), sizeof(monto));
    }
}

void aplicarDescuentoMonto(int fechaLeida, int fechaLimite, char gravedad, double& monto) {
    if (fechaLeida < fechaLimite) {
        switch (gravedad) {
            case 'L':
                monto = 0;
                break;
            case 'G':
                monto *= 0.25;
                break;
            case 'M':
                monto *= 0.08;
                break;
        }
    }
}

int solicitarFecha() {
    int dd, mm, aaaa;
    char c;
    cout << "Ingrese una fecha en el formato dd/mm/aaaa: ";
    cin >> dd >> c >> mm >> c >> aaaa;
    return convertirFecha(dd, mm, aaaa);
}

/* Reportes */

void imprimirReporte(const char* nomArch) {
    ofstream archReporte = crearArchTexto(nomArch);
    imprimirConductores(archReporte);
    imprimirFaltas(archReporte);
    imprimirInfracciones(archReporte);
}

void imprimirReporteConductores(const char* nomArch) {
    ofstream archReporte = crearArchTexto(nomArch);
    imprimirConductores(archReporte);
    imprimirFaltas(archReporte);
}

void imprimirReporteInfracciones(const char* nomArch) {
    ofstream archReporte = crearArchTexto(nomArch);
    imprimirInfracciones(archReporte);
}

void imprimirConductores(ofstream& archRep) {
    // Abrir el archivo y calcular el número de registros
    ifstream archBin = abrirArchBin("Conductores.bin");
    int numReg = calcularNumRegistros(archBin, TAM_REG_CONDUCTORES);
    // Imprimir cabecera
    archRep << fixed << setprecision(2)
            << left << setw(10) << "Licencia" << setw(MAX_NOM_CONDUCTOR) << "Nombre"
            << right << setw(5) << "#Leve" << setw(8) << "#Grave" << setw(11) << "#MuyGrave"
            << setw(10) << "$Leve" << setw(9) << "$Grave" << setw(11) << "$MuyGrave"
            << setw(12) << "$Total" << endl;
    // Leer línea por línea
    char nombre[MAX_NOM_CONDUCTOR];
    int licencia, numLeve, numGrave, numMuyGrave;
    double montoLeve, montoGrave, montoMuyGrave, montoTotal;
    for (int i = 0; i < numReg; i++) {
        archBin.read(reinterpret_cast<char*>(&licencia), sizeof(licencia));
        archBin.read(reinterpret_cast<char*>(nombre), sizeof(nombre));
        archBin.read(reinterpret_cast<char*>(&numLeve), sizeof(numLeve));
        archBin.read(reinterpret_cast<char*>(&numGrave), sizeof(numGrave));
        archBin.read(reinterpret_cast<char*>(&numMuyGrave), sizeof(numMuyGrave));   
        archBin.read(reinterpret_cast<char*>(&montoLeve), sizeof(montoLeve));
        archBin.read(reinterpret_cast<char*>(&montoGrave), sizeof(montoGrave));
        archBin.read(reinterpret_cast<char*>(&montoMuyGrave), sizeof(montoMuyGrave));
        archBin.read(reinterpret_cast<char*>(&montoTotal), sizeof(montoTotal));
        archRep << left << setw(10) << licencia << setw(MAX_NOM_CONDUCTOR) << nombre
                << right << setw(5) << numLeve << setw(8) << numGrave << setw(11) << numMuyGrave
                << setw(10) << montoLeve << setw(9) << montoGrave << setw(11) << montoMuyGrave
                << setw(12) << montoTotal << endl;
    }
    archRep << endl;
}

void imprimirFaltas(ofstream& archRep) {
    // Abrir el archivo y calcular el número de registros
    ifstream archFaltas = abrirArchBin("FaltasCometidas.bin");
    int numReg = calcularNumRegistros(archFaltas, TAM_REG_FALTAS);
    // Imprimir cabecera
    archRep << fixed << setprecision(2)
            << left << setw(9) << "Placa" << setw(10) << "Licencia" << setw(12) << "Fecha"
            << setw(11) << "Gravedad" << setw(8) << "Codigo" << setw(5) << "Monto" << endl;
    // Leer línea por línea
    char placa[MAX_PLACA], gravedad[MAX_GRAVEDAD];
    int licencia, fecha, codigo;
    double monto;
    for (int i = 0; i < numReg; i++) {
        archFaltas.read(reinterpret_cast<char*>(placa), sizeof(placa));
        archFaltas.read(reinterpret_cast<char*>(&licencia), sizeof(licencia));
        archFaltas.read(reinterpret_cast<char*>(&fecha), sizeof(fecha));
        archFaltas.read(reinterpret_cast<char*>(gravedad), sizeof(gravedad));
        archFaltas.read(reinterpret_cast<char*>(&codigo), sizeof(codigo));
        archFaltas.read(reinterpret_cast<char*>(&monto), sizeof(monto));
        // Imprimir datos en el reporte
        archRep << left << setw(9) << placa << setw(10) << licencia;
        imprimirFecha(archRep, fecha);
        archRep << right << setw(11) << gravedad << setw(8) << codigo << setw(9) << monto << endl;
    }
    archRep << endl;
}

void imprimirInfracciones(ofstream& archRep) {
    // Abrir el archivo y calcular el número de registros
    ifstream archBin = abrirArchBin("Infracciones.bin");
    int numReg = calcularNumRegistros(archBin, TAM_REG_INFRACCIONES);
    // Imprimir cabecera
    archRep << fixed << setprecision(2) << left
            << setw(8) << "Codigo" << setw(MAX_NOM_INFRACCION) << "Nombre"
            << setw(11) << "Gravedad" << "Monto" << endl;
    // Leer línea por línea
    char nombre[MAX_NOM_INFRACCION], gravedad[MAX_GRAVEDAD];
    int codigo;
    double monto;
    for (int i = 0; i < numReg; i++) {
        archBin.read(reinterpret_cast<char*>(&codigo), sizeof(codigo));
        archBin.read(reinterpret_cast<char*>(nombre), sizeof(nombre));
        archBin.read(reinterpret_cast<char*>(gravedad), sizeof(gravedad));
        archBin.read(reinterpret_cast<char*>(&monto), sizeof(monto));
        archRep << left << setw(8) << codigo << setw(MAX_NOM_INFRACCION) << nombre
                << right << setw(9) << gravedad << setw(10) << monto << endl;
    }
}

/* Funciones auxiliares */

ifstream abrirArchTexto(const char* nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream crearArchTexto(const char* nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ifstream abrirArchBin(const char* nomArch) {
    ifstream arch(nomArch, ios::in | ios::binary);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream crearArchBin(const char* nomArch) {
    ofstream arch(nomArch, ios::out | ios::binary);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

fstream actualizarArchBin(const char* nomArch) {
    fstream arch(nomArch, ios::in | ios::out | ios::binary);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

int calcularNumRegistros(istream& archBin, int tamReg) {
    archBin.seekg(0, ios::end);
    int numReg = archBin.tellg() / tamReg;
    archBin.seekg(0, ios::beg);
    return numReg;
}

int convertirFecha(int dd, int mm, int aaaa) {
    return 10000*aaaa + 100*mm + dd;
}

void imprimirFecha(ofstream& archivo, int fecha) {
    int aaaa = fecha/10000, mm = (fecha/100)%100, dd = fecha%100;
    archivo << right << setfill('0')
            << setw(2) << dd << '/' << setw(2) << mm << '/' << setw(4) << aaaa
            << setfill(' ');
}
