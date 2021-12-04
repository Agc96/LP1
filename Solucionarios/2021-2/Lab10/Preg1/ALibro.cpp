/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ALibro.cpp
 * Author: Anthony
 * 
 * Created on 3 de diciembre de 2021, 08:16 AM
 */

#include "ALibro.h"

ALibro::ALibro() {
    Raiz = nullptr;
}

ALibro::ALibro(const ALibro& orig) {
}

ALibro::~ALibro() {
    if (Raiz) delete Raiz;
}

