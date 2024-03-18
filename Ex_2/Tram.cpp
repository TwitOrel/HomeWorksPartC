//
// Created by Orel on 23/02/2024.
//

#include "Tram.h"

Tram::Tram(int distance) : Vehicles(distance) {}

char Tram::getType() const {
    return 't';
}

void Tram::setExchange(int d) {
    exchange = d;
}

int Tram::getExchange() const {
    return exchange;
}

int Tram::exchange = 3;

