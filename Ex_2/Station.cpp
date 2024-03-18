//
// Created by Orel on 21/02/2024.
//

#include "Station.h"

#include <utility>

Station::Station(string n) : name(std::move(n)) {}

const string &Station::getName() const {
    return this->name;
}

bool Station::operator<(const Station &a) const {
    return this->name < a.name;
}

bool Station::operator==(const Station &a) const {
    return this->name == a.name;
}

ostream &operator<<(ostream &os, const Station &s) {
    os << s.getName();
    return os;
}