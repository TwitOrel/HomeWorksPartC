//
// Created by Orel on 01/02/2024.
//

#include <cstdlib>
#include "BQ.h"



BQ::BQ(const vector<char> &v,const RCPtr<SARS_CoV_2> &parent) : SARS_CoV_2(v,parent){}

BQ &BQ::operator=(const BQ &v) {
    if (this == &v){
        return *this;
    }
    this->DNA = v.DNA;
    this->DNA = v.DNA;
    return *this;
}

float BQ::ratioOfHit(const vector<char> &of, int dimension)const {
    return float(sumOfHit(of,dimension))/float(dimension);
}

void BQ::personalUpdate() {
    for(char &c: DNA){
        switch (c) {
            case 'A':
                if (rand() % (int)DNA.size()-1 + 1 == 1){
                    c = 'T';
                }
                break;
            case 'C':
                if (rand() % (int)DNA.size()-1 + 1 == 1){
                    c = 'G';
                }
                break;
            case 'G':
                if (rand() % (int)DNA.size()-1 + 1 == 1){
                     c = 'C';
                }
                break;
            default:
                continue;
        }
    }
}


