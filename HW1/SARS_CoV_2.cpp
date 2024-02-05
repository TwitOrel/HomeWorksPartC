
#include <iostream>
#include "SARS_CoV_2.h"
using namespace std;

SARS_CoV_2::SARS_CoV_2(const SARS_CoV_2 &of) = default;

SARS_CoV_2::SARS_CoV_2(const vector<char> &of, const RCPtr<SARS_CoV_2> &parent):parent(parent),DNA(of){}

SARS_CoV_2 &SARS_CoV_2::operator=(const SARS_CoV_2 &v) {
    if (this == &v){
        return *this;
    }
    parent = v.parent;
    DNA = v.DNA;
    return *this;
}

const vector<char>& SARS_CoV_2::getParentDNA() const {
    return parent->DNA;
}

const RCPtr<SARS_CoV_2> &SARS_CoV_2::getParent() const {
    return parent;
}

const vector<char> &SARS_CoV_2::getDNA()const {
    return this->DNA;
}

int SARS_CoV_2::sumOfHit(const vector<char> &of,int dimension)const {
    int k = 0;
    for (int i = 0; i < dimension; ++i) {
        if (of[i] == this->DNA[i + 1]){
            k++;
        }
    }
    return k;
}

float SARS_CoV_2::ratioOfHit(const vector<char> &of, int dimension)const {
    return  (float)sumOfHit(of,dimension) / (float)dimension;
}

void SARS_CoV_2::print() {
    for (char c:DNA){
        cout << c << " ";
    }
    cout << endl;
}