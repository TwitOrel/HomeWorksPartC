//
// Created by Orel on 23/02/2024.
//

#ifndef EX_2_SPRINTER_H
#define EX_2_SPRINTER_H

#include "Vehicles.h"

class Sprinter : public Vehicles {
    // represent the time by exchanging stations
    static int exchange;

public:
    explicit Sprinter(int distance);

    // return 's' (type of sprinter)
    char getType() const override;

    // set exchange (from config file)
    static void setExchange(int d);

    // get the exchange (while sprinter move to another station)
    int getExchange() const override;

};

#endif //EX_2_SPRINTER_H
