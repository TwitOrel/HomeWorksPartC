//
// Created by Orel on 01/02/2024.
//

#ifndef HW1_CH_H
#define HW1_CH_H

#include "SARS_CoV_2.h"

class CH : public SARS_CoV_2{
private:
public:
    CH(const vector<char>&,const RCPtr<SARS_CoV_2> &parent);
    CH& operator=(const CH&);
    ~CH()override = default;
    float ratioOfHit(const vector<char> &of, int dimension)const override;
    void personalUpdate() override;
};
#endif //HW1_CH_H
