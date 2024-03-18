//
// Created by Orel on 23/02/2024.
//

#include "Rail.h"

Rail::Rail(int distance) : Vehicles(distance) {}

char Rail::getType() const {
    return 'r';
}

void Rail::setExchange(int d) {
    exchange = d;
}

int Rail::getExchange() const {
    return exchange;
}

int Rail::exchange = 5;

