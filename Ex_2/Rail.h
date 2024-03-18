//
// Created by Orel on 23/02/2024.
//

#ifndef EX_2_RAIL_H
#define EX_2_RAIL_H

#include "Vehicles.h"

class Rail : public Vehicles {
    // represent the time by exchanging stations
    static int exchange;

public:
    explicit Rail(int distance);

    // return 'r' (type of rail)
    char getType() const override;

    // set exchange (from config file)
    static void setExchange(int d);

    // get the exchange (while rail move to another station)
    int getExchange() const override;

};

#endif //EX_2_RAIL_H
