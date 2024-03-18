//
// Created by Orel on 23/02/2024.
//

#include "Sprinter.h"

Sprinter::Sprinter(int distance) : Vehicles(distance) {}

char Sprinter::getType() const {
    return 's';
}

void Sprinter::setExchange(int d) {
    exchange = d;
}

int Sprinter::getExchange() const {
    return exchange;
}

int Sprinter::exchange = 4;

