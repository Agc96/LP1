/*
 * Archivo: Medico.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Medico.h"
using namespace std;

#define MAX_BUFFER 100
#define MAX_SEPARACION 60

Medico::Medico() {
    inicializar();
}

Medico::Medico(const Medico& orig) {
    inicializar();
    *this = orig;
}

Medico::~Medico() {
    if (codigo) delete codigo;
    if (nombre) delete nombre;
    if (especialidad) delete especialidad;
}

void Medico::inicializar() {
    codigo = nullptr;
    nombre = nullptr;
    especialidad = nullptr;
    numPac = 0;
    ingresosP = 0;
    ingresosS = 0;
}

/* Sobrecargas de la clase */

Medico& Medico::operator =(const Medico& orig) {
    // Copiar datos principales
    setCodigo(orig.codigo);
    setNombre(orig.nombre);
    setEspecialidad(orig.especialidad);
    setTarifa(orig.tarifa);
    // Copiar arreglos de pacientes
    for (int i = 0; i < orig.numPac; i++) {
        this->fechas[i] = orig.fechas[i];
        this->pacientes[i] = orig.pacientes[i];
        this->prima[i] = orig.pacientes[i];
        this->estado[i] = orig.estado[i];
    }
    this->numPac = orig.numPac;
    // Copiar totales de ingresos
    this->ingresosP = orig.ingresosP;
    this->ingresosS = orig.ingresosS;
    return *this;
}

void Medico::operator +(Paciente& paciente) {
    fechas[numPac] = paciente.getFecha();
    pacientes[numPac] = paciente.getCodigo();
    prima[numPac] = paciente.getPrima();
    estado[numPac] = paciente.getEstado();
    numPac++;
}

void Medico::operator *(int fecha) {
    for (int i = 0; i < numPac; i++) {
        if (fechas[i] == fecha && estado[i] == 'R') {
            estado[i] = 'A';
        }
    }
}

void Medico::operator -(int fecha) {
    for (int i = 0; i < numPac; i++) {
        if (fechas[i] == fecha && estado[i] == 'R') {
            estado[i] = 'E';
        }
    }
}

void Medico::operator ++() {
    ingresosP = ingresosS = 0;
    for (int i = 0; i < numPac; i++) {
        if (estado[i] == 'A') {
            ingresosP += tarifa * prima[i] / 100;
            ingresosS += tarifa * (100-prima[i]) / 100;
        }
    }
}

/* Encapsulamiento */

char* Medico::getCodigo() {
    return crearCadena(codigo);
}

void Medico::setCodigo(char* codigo) {
    if (this->codigo) delete this->codigo;
    this->codigo = crearCadena(codigo);
}

char* Medico::getEspecialidad() {
    return crearCadena(especialidad);
}

void Medico::setEspecialidad(char* especialidad) {
    if (this->especialidad) delete this->especialidad;
    this->especialidad = crearCadena(especialidad);
}

char* Medico::getNombre() const {
    return nombre;
}

void Medico::setNombre(char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = crearCadena(nombre);
}

double Medico::getTarifa() const {
    return tarifa;
}

void Medico::setTarifa(double tarifa) {
    this->tarifa = tarifa;
}

char* Medico::crearCadena(char* buffer) {
    if (buffer == nullptr) return nullptr;
    char* cad = new char[strlen(buffer)+1];
    strcpy(cad, buffer);
    return cad;
}

/* Métodos de lectura e impresión */

istream& Medico::leer(istream& in) {
    char buffer[MAX_BUFFER];
    // Leer el código del médico
    in >> buffer;
    if (in.eof()) return in;
    setCodigo(buffer);
    // Leer el nombre del médico
    in >> buffer;
    setNombre(buffer);
    // Leer la especialidad del médico
    in >> buffer;
    setEspecialidad(buffer);
    // Leer la tarifa del médico
    in >> tarifa;
    return in;
}

ostream& Medico::imprimir(ostream& out) {
    out << fixed << setprecision(2);
    // Imprimir datos principales
    out << "Medico: " << nombre << endl;
    out << "Codigo: " << codigo << endl;
    out << "Especialidad: " << especialidad << endl;
    out << "Honorarios por cita: " << tarifa << endl;
    separacion(out, '=');
    // Imprimir pacientes atendidos
    out << "Pacientes atendidos:" << endl;
    separacion(out, '-');
    imprimirPacientes(out, 'A');
    separacion(out, '=');
    // Imprimir pacientes por atender
    out << "Pacientes por atender:" << endl;
    separacion(out, '-');
    imprimirPacientes(out, 'R');
    separacion(out, '=');
    // Imprimir resumen
    out << "Monto total recibido por pacientes: " << setw(8) << ingresosP << endl;
    out << "Monto a solicitar al seguro: " << setw(15) << ingresosS << endl;
    return out;
}

void Medico::imprimirPacientes(ostream& out, char estadoBuscado) {
    double pago, seguro;
    int cont = 0;
    // Imprimir cabecera
    out << "No." << setw(10) << "Fecha" << setw(20) << "Paciente";
    if (estadoBuscado == 'A') {
        out << setw(10) << "Pago" << setw(15) << "Seguro";
    }
    out << endl;
    // Imprimir lista de pacientes
    for (int i = 0; i < numPac; i++) {
        if (estado[i] == estadoBuscado) {
            imprimirContador(out, ++cont);
            imprimirFecha(out, fechas[i]);
            out << setw(15) << pacientes[i];
            if (estadoBuscado == 'A') {
                pago = tarifa * prima[i] / 100;
                seguro = tarifa * (100-prima[i]) / 100;
                out << setw(12) << pago << setw(15) << seguro;
            }
            out << endl;
        }
    }
}

void Medico::imprimirContador(ostream& out, int contador) {
    int width;
    if (contador >= 100) {
        width = 3;
    } else if (contador >= 10) {
        width = 2;
    } else {
        width = 1;
    }
    out << setw(width) << contador << ')';
    out << setw(7-width) << ' ';
}

void Medico::imprimirFecha(ostream& out, int fecha) {
    int dia = fecha % 100;
    int mes = (fecha / 100) % 100;
    int anho = fecha / 10000;
    out << setfill('0');
    out << setw(2) << dia << '/';
    out << setw(2) << mes << '/';
    out << setw(4) << anho;
    out << setfill(' ');
}

void Medico::separacion(ostream& out, char c) {
    for (int i = 0; i < MAX_SEPARACION; i++) {
        out.put(c);
    }
    out << endl;
}

/* Sobrecargas de lectura e impresión */

istream& operator >>(istream& in, Medico& medico) {
    return medico.leer(in);
}

ostream& operator <<(ostream& out, Medico& medico) {
    return medico.imprimir(out);
}
