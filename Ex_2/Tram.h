//
// Created by Orel on 23/02/2024.
//

#ifndef EX_2_TRAM_H
#define EX_2_TRAM_H
#include "Vehicles.h"
class Tram : public Vehicles{
    // represent the time by exchanging stations
    static int exchange;

public:
    explicit Tram(int distance);

    // return 't' (type of tram)
    char getType()const override;

    // set exchange (from config file)
    static void setExchange(int d);

    // get the exchange (while tram move to another station)
    int getExchange()const override;

};

#endif //EX_2_TRAM_H
