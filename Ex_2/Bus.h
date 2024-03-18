//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_BUS_H
#define EX_2_BUS_H

#include "Vehicles.h"

class Bus : public Vehicles {
    // represent the time by exchanging stations
    static int exchange;

public:
    explicit Bus(int distance);

    // return 'b' (type of bus)
    char getType() const override;

    // set exchange (from config file)
    static void setExchange(int d);

    // get the exchange (while bus move to another station)
    int getExchange() const override;

};

#endif //EX_2_BUS_H
