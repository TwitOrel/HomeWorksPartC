//
// Created by Orel on 01/02/2024.
//

#include <cstdlib>
#include "CH.h"


CH::CH(const vector<char> &v,const RCPtr<SARS_CoV_2> &parent) : SARS_CoV_2(v,parent){}

CH &CH::operator=(const CH &v) {
    if (this == &v){
        return *this;
    }
    this->DNA = v.DNA;
    this->DNA = v.DNA;
    return *this;
}

float CH::ratioOfHit(const vector<char> &of, int dimension)const {
    return float(sumOfHit(of,dimension))/float(dimension);
}

void CH::personalUpdate() {

    for(char &c: DNA){
        switch (c) {
            case 'T':
                if (rand() % (int)DNA.size()-1 + 1 <= (int)DNA.size()-1){
                    c = 'A';
                }
                break;
            case 'C':
                if (rand() % (int)DNA.size()-1 + 1 <= (int)DNA.size()-1){
                    c = 'G';
                }
                break;
            case 'G':
                if (rand() % (int)DNA.size()-1 + 1 <= (int)DNA.size()-1){
                    c = 'C';
                }
                break;
            default:
                continue;
        }
    }
}