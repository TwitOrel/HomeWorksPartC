//
// Created by Orel on 21/02/2024.
//

#include "Intercity.h"


Intercity::Intercity(const string &name) : Station(name) {
}

string Intercity::getType() const {
    return "IC";
}

void Intercity::setExchange(int d) {
    exchange = d;
}

int Intercity::getExchange() const {
    return exchange;
}

int Intercity::exchange = 15;