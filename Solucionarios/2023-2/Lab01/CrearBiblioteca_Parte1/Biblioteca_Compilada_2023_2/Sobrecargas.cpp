/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Sobrecargas.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 06:40 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Sobrecargas.h"
using namespace std;

bool operator >>(ifstream &arch, Cliente &cliente) {
    arch >> cliente.dni;
    if (arch.eof()) return false;
    arch.get();
    arch.getline(cliente.nombre, 60, ',');
    arch >> cliente.telefono >> ws;
    cliente.cantidadProductosEntrgados = 0;
    cliente.montoTotal = 0;
    return true;
}

bool operator >>(ifstream &arch, Producto &producto) {
    arch.getline(producto.codigo, 8, ',');
    if (arch.eof()) return false;
    arch.getline(producto.descripcion, 60, ',');
    arch >> producto.precio;
    arch.get();
    arch >> producto.stock >> ws;
    producto.cantidadClientesServidos = 0;
    producto.cantidadClientesNoServidos = 0;
    return true;
}

bool operator >>(ifstream &arch, Pedido &pedido) {
    arch.getline(pedido.CodigoProducto, 8, ',');
    if (arch.eof()) return false;
    arch >> pedido.dniCliente >> ws;
    pedido.precioProducto = 0;
    return true;
}

void operator +=(Cliente *clientes, Pedido &pedido) {
    int indice;
    for (int i = 0; clientes[i].dni != 0; i++) {
        if (clientes[i].dni == pedido.dniCliente) {
            indice = clientes[i].cantidadProductosEntrgados;
            strcpy(clientes[i].productosEntregados[indice].codigo, pedido.CodigoProducto);
            clientes[i].productosEntregados[indice].precio = pedido.precioProducto;
            clientes[i].cantidadProductosEntrgados++;
            clientes[i].montoTotal += pedido.precioProducto;
            return;
        }
    }
}

bool operator +=(Producto *productos, Pedido &pedido) {
    int indice;
    for (int i = 0; strcmp(productos[i].codigo, "XXXXXXX") != 0; i++) {
        if (strcmp(productos[i].codigo, pedido.CodigoProducto) == 0) {
            pedido.precioProducto = productos[i].precio;
            if (productos[i].stock > 0) {
                productos[i].stock--;
                indice = productos[i].cantidadClientesServidos;
                productos[i].clientesServidos[indice] = pedido.dniCliente;
                productos[i].cantidadClientesServidos++;
                return true;
            } else {
                indice = productos[i].cantidadClientesNoServidos;
                productos[i].clientesNoServidos[indice] = pedido.dniCliente;
                productos[i].cantidadClientesNoServidos++;
                break;
            }
        }
    }
    return false;
}

void operator <<(ofstream &arch, Cliente &cliente) {
    arch << fixed << setprecision(2);
    arch << right << setw(8) << cliente.dni << "  " << left << setw(60) << cliente.nombre;
    arch << right << setw(10) << cliente.telefono << setw(10) << cliente.montoTotal;
    // Verificar productos entregados
    if (cliente.cantidadProductosEntrgados > 0) {
        arch << left << setw(25) << "  Productos entregados:";
        for (int i = 0; i < cliente.cantidadProductosEntrgados; i++) {
            arch << left << setw(10) << cliente.productosEntregados[i].codigo;
        }
        arch << endl;
    } else {
        arch << "  NO SE LE ENTREGARON PRODUCTOS" << endl;
    }
}

void operator <<(ofstream &arch, Producto &producto) {
    arch << fixed << setprecision(2);
    arch << left << setw(10) << producto.codigo << setw(60) << producto.descripcion;
    arch << right << setw(10) << producto.precio << setw(5) << producto.stock << endl;
    // Imprimir clientes atendidos
    if (producto.cantidadClientesServidos > 0) {
        arch << left << setw(25) << "Clientes atendidos: ";
        for (int i = 0; i < producto.cantidadClientesServidos; i++) {
            arch << right << setw(10) << producto.clientesServidos[i];
        }
        arch << endl;
    } else {
        arch << "NO SE ATENDIERON PEDIDOS" << endl;
    }
    // Imprimir clientes no atendidos
    if (producto.cantidadClientesNoServidos > 0) {
        arch << left << setw(25) << "Clientes no atendidos:";
        for (int i = 0; i < producto.cantidadClientesNoServidos; i++) {
            arch << right << setw(10) << producto.clientesNoServidos[i];
        }
        arch << endl;
    } else {
        arch << "NO HAY CLIENTES SIN ATENDER" << endl;
    }
}
