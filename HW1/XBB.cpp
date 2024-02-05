//
// Created by Orel on 30/01/2024.
//

#include <cstdlib>
#include "XBB.h"

XBB::XBB(const vector<char> &v,const RCPtr<SARS_CoV_2> &parent) : SARS_CoV_2(v,parent){}

XBB &XBB::operator=(const XBB &v) {
    if (this == &v){
        return *this;
    }
    this->DNA = v.DNA;
    this->DNA = v.DNA;
    return *this;
}

float XBB::ratioOfHit(const vector<char> &of, int dimension)const {
    return float(sumOfHit(of,dimension))/float(dimension);
}

void XBB::personalUpdate() {
    for(char &c: DNA){
        switch (c) {
            case 'A':
                if ((rand() % 4) + 1 == 1){
                    c = 'T';
                }
                break;
            case 'T':
                if ((rand() % 4) + 1 == 1){
                    c = 'A';
                }
                break;
            default:
                continue;
        }
    }
}
