//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_VEHICLES_H
#define EX_2_VEHICLES_H

class Vehicles {
    // represent the distance between stations
    int distance;

public:
    explicit Vehicles(int d);

    // return the distance between 2 stations
    int getDistance() const;

    // set distance between 2 stations
    void setDistance(int d);

    virtual int getExchange() const = 0;

    virtual char getType() const = 0;
};

#endif //EX_2_VEHICLES_H
