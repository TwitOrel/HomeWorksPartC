//
// Created by Orel on 30/01/2024.
//

#ifndef HW1_SARS_COV_2_H
#define HW1_SARS_COV_2_H
using namespace std;
#include <vector>
#include "RCPtr.h"

class SARS_CoV_2{

protected:
    RCPtr<SARS_CoV_2> parent;
    vector<char> DNA;
public:
    SARS_CoV_2(const vector<char> &of, const RCPtr<SARS_CoV_2> &parent);
    SARS_CoV_2(const SARS_CoV_2 &virus);
    SARS_CoV_2& operator=(const SARS_CoV_2 &v);
    virtual ~SARS_CoV_2() = default;

    const vector<char>& getParentDNA()const;
    const RCPtr<SARS_CoV_2>& getParent() const;
    const vector<char>& getDNA()const;
    int sumOfHit(const vector<char> &of,int dimension)const;
    virtual float ratioOfHit(const vector<char> &of, int dimension)const;
    virtual void personalUpdate() = 0;
    void print();

};
#endif //HW1_SARS_COV_2_H