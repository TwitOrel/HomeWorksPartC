//
// Created by Orel on 29/02/2024.
//

#include "Stad.h"

Stad::Stad(const string &name) : Station(name) {
}

string Stad::getType() const {
    return "S";
}

void Stad::setExchange(int d) {
    exchange = d;
}

int Stad::getExchange() const {
    return exchange;
}

int Stad::exchange = 10;