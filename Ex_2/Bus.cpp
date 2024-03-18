//
// Created by Orel on 21/02/2024.
//

#include "Bus.h"

Bus::Bus(int distance) : Vehicles(distance) {}

char Bus::getType() const {
    return 'b';
}

void Bus::setExchange(int d) {
    exchange = d;
}

int Bus::getExchange() const {
    return exchange;
}

int Bus::exchange = 2;
