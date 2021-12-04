/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NLibro.cpp
 * Author: Anthony
 * 
 * Created on 3 de diciembre de 2021, 08:16 AM
 */

#include "NLibro.h"

NLibro::NLibro() {
    izq = nullptr;
    der = nullptr;
}

NLibro::NLibro(const NLibro& orig) {
}

NLibro::~NLibro() {
    if (izq) delete izq;
    if (der) delete der;
}
