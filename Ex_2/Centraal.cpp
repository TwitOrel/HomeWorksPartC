//
// Created by Orel on 29/02/2024.
//

#include "Centraal.h"

Centraal::Centraal(const string &name) : Station(name) {
}

string Centraal::getType() const {
    return "CS";
}

void Centraal::setExchange(int d) {
    exchange = d;
}

int Centraal::getExchange() const {
    return exchange;
}

int Centraal::exchange = 5;