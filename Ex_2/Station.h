//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_STATION_H
#define EX_2_STATION_H

#include <string>
#include <iostream>

using namespace std;

class Station {
    // name of station
    string name;


public:
    explicit Station(string n);

    // return name of station
    const string &getName() const;

    virtual void setExchange(int d) = 0;

    virtual string getType() const = 0;

    virtual int getExchange() const = 0;

    // for comparator
    bool operator<(const Station &a) const;

    // for check if station is the same by name
    bool operator==(const Station &a) const;

};

// add to os the name os the station
ostream &operator<<(ostream &os, const Station &s);

#endif //EX_2_STATION_H