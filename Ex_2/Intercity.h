//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_INTERCITY_H
#define EX_2_INTERCITY_H

#include "Station.h"
#include <iostream>

class Intercity : public Station {
    // represent the time by exchanging stations
    static int exchange;

public:

    explicit Intercity(const string &name);

    // return type 'IC' (type of station)
    string getType() const override;

    // set exchange (from config file)
    void setExchange(int d) override;

    // get the exchange (while chancing vehicle)
    int getExchange() const override;

};


#endif //EX_2_INTERCITY_H
