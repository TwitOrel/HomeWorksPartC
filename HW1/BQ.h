//
// Created by Orel on 01/02/2024.
//

#ifndef HW1_BQ_H
#define HW1_BQ_H
#include "SARS_CoV_2.h"

class BQ : public SARS_CoV_2{
private:
public:
    BQ(const vector<char>&,const RCPtr<SARS_CoV_2> &parent);
    BQ& operator=(const BQ&);
    ~BQ()override = default;

    float ratioOfHit(const vector<char> &of, int dimension)const override;
    void personalUpdate() override;
};
#endif //HW1_BQ_H
