/*
 * Archivo: BibMedicos.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de octubre de 2020, 08:54 AM
 */

#include "BibMedicos.h"
#define STMEDICO_MAX_LINEA 50

/* Lectura */

istream& operator >>(istream& in, StMedico& medico) {
    in >> medico.codigo >> medico.nombre >> medico.especialidad >> medico.tarifa;
    return in;
}

istream& operator >>(istream& in, StPaciente& paciente) {
    in >> paciente.estado >> paciente.codigo >> paciente.nombre >> paciente.prima;
    return in;
}

/* Agregación */

void operator +(StMedico& medico, StPaciente& paciente) {
    medico.fechas[medico.numPac] = paciente.fecha;
    medico.pacientes[medico.numPac] = paciente.codigo;
    medico.prima[medico.numPac] = paciente.prima;
    medico.estado[medico.numPac] = paciente.estado;
    medico.numPac++;
}

/* Modificación de estado */

void operator +(StMedico& medico, int fecha) {
    for (int i = 0; i < medico.numPac; i++) {
        if (medico.fechas[i] == fecha && medico.estado[i] == 'R') {
            medico.estado[i] = 'A';
        }
    }
}

/* Cancelación de citas */

void operator -(StMedico& medico, int fecha) {
    for (int i = 0; i < medico.numPac; i++) {
        if (medico.fechas[i] == fecha && medico.estado[i] == 'R') {
            // Remover las fechas
            for (int j = i; j < medico.numPac; j++) {
                medico.fechas[j] = medico.fechas[j+1];
                medico.pacientes[j] = medico.pacientes[j+1];
                medico.prima[j] = medico.prima[j+1];
                medico.estado[j] = medico.estado[j+1];
            }
            // Actualizar contadores
            medico.numPac--;
            i--;
        }
    }
}

/* Descarte */

void operator /(StMedico& medico, int fecha) {
    for (int i = 0; i < medico.numPac; i++) {
        if (medico.fechas[i] < fecha) {
            // Remover las fechas
            for (int j = i; j < medico.numPac; j++) {
                medico.fechas[j] = medico.fechas[j+1];
                medico.pacientes[j] = medico.pacientes[j+1];
                medico.prima[j] = medico.prima[j+1];
                medico.estado[j] = medico.estado[j+1];
            }
            // Actualizar contadores
            medico.numPac--;
            i--;
        }
    }
}

/* Cálculo de ingresos */

void operator ++(StMedico& medico) {
    medico.ingresosP = 0;
    medico.ingresosS = 0;
    for (int i = 0; i < medico.numPac; i++) {
        if (medico.estado[i] == 'A') {
            medico.ingresosP += medico.prima[i] * medico.tarifa / 100;
            medico.ingresosS += (100 - medico.prima[i]) * medico.tarifa / 100;
        }
    }
}

/* Impresión */

ostream& operator <<(ostream& out, StMedico& medico) {
    out << left << fixed << setprecision(2);
    // Imprimir datos generales
    out << "Medico: " << medico.nombre << endl;
    out << "Codigo: " << medico.codigo << endl;
    out << "Especialidad: " << medico.especialidad << endl;
    out << "Honorarios por cita: " << medico.tarifa << endl;
    imprimirLinea(out, '=');
    // Imprimir lista de pacientes atendidos
    out << "Pacientes atendidos:" << endl;
    imprimirLinea(out, '-');
    imprimirPacientes(out, medico, 'A');
    imprimirLinea(out, '=');
    // Imprimir lista de pacientes por atender
    out << "Pacientes por atender:" << endl;
    imprimirLinea(out, '-');
    imprimirPacientes(out, medico, 'R');
    imprimirLinea(out, '=');
    // Imprimir resumen
    out << right << "Monto total recibido por pacientes: " << setw(9) << medico.ingresosP << endl;
    out << "Monto a solicitar al seguro: " << setw(16) << medico.ingresosS << endl;
    return out;
}

void imprimirPacientes(ostream& out, StMedico& medico, char estado) {
    int contador = 0;
    // Imprimir cabecera
    out << left << setw(5) << "No." << setw(12) << "Fecha" << setw(10) << "Paciente";
    if (estado == 'A') {
        out << setw(10) << "Pago" << setw(8) << "Seguro";
    }
    out << endl;
    // Imprimir lista de médicos con el estado solicitado
    for (int i = 0; i < medico.numPac; i++) {
        if (medico.estado[i] == estado) {
            contador++;
            // Imprimir contador y fecha
            imprimirContador(out, contador);
            imprimirFecha(out, medico.fechas[i]);
            // Imprimir código del paciente
            out << left << setfill('0') << setw(6) << medico.pacientes[i];
            out << setfill(' ') << setw(4) << ' ';
            // Imprimir pago y seguro si es un paciente atendido
            if (estado == 'A') {
                out << right << setw(8) << medico.prima[i] * medico.tarifa / 100;
                out << setw(2) << ' ';
                out << setw(8) << (100 - medico.prima[i]) * medico.tarifa / 100;
            }
            out << endl;
        }
    }
}

/* Funciones auxiliares */

void imprimirContador(ostream& out, int contador) {
    int fill = contador < 10 ? 3 : (contador < 100 ? 2 : 1);
    // Imprimir contador
    out << left << contador << ')' << setw(fill) << ' ';
}

void imprimirFecha(ostream& out, int fecha) {
    // Descomponer fecha
    int dia = fecha % 100;
    int mes = (fecha / 100) % 100;
    int anho = fecha / 10000;
    // Imprimir fecha en el formato dd/mm/aaaa
    out << right << setfill('0') << setw(2) << dia << '/';
    out << setw(2) << mes << '/';
    out << setw(4) << anho << setfill(' ') << setw(2) << ' ';
}

void imprimirLinea(ostream& out, char c) {
    for (int i = 0; i < STMEDICO_MAX_LINEA; i++) {
        out.put(c);
    }
    out << endl;
}
