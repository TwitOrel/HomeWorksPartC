//
// Created by Orel on 21/02/2024.
//

#include <stdexcept>
#include "Vehicles.h"

using namespace std;

Vehicles::Vehicles(int d) : distance(d) {
    if (d < 0) {
        throw invalid_argument("Vehicles C'tor: distance between 2 Stations cant be Negative");
    }
}

void Vehicles::setDistance(int x) {
    if (x < 0) {
        throw invalid_argument("setDistance: distance between 2 Stations cant be Negative");
    }
    if (this->distance > x)
        this->distance = x;
}

int Vehicles::getDistance() const {
    return this->distance;
}