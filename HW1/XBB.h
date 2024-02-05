//
// Created by Orel on 30/01/2024.
//

#ifndef HW1_XBB_H
#define HW1_XBB_H
#include "SARS_CoV_2.h"

class XBB : public SARS_CoV_2{
private:
public:
    XBB(const vector<char>&,const RCPtr<SARS_CoV_2> &parent);
    XBB& operator=(const XBB&);
    ~XBB()override = default;

    float ratioOfHit(const vector<char> &of, int dimension) const override;
    void personalUpdate() override;
};
#endif //HW1_XBB_H
