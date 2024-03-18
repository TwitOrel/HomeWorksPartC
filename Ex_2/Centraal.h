//
// Created by Orel on 29/02/2024.
//

#ifndef EX_2_CENTRAAL_H
#define EX_2_CENTRAAL_H

#include "Station.h"
#include <iostream>

class Centraal : public Station {
    // represent the time by exchanging stations
    static int exchange;

public:

    explicit Centraal(const string &name);

    // return type 'CS' (type of station)
    string getType() const override;

    // set exchange (from config file)
    void setExchange(int d) override;

    // get the exchange (while chancing vehicle)
    int getExchange() const override;

};

#endif //EX_2_CENTRAAL_H
