//
// Created by Orel on 30/01/2024.
//

#ifndef HW1_WORLD_H
#define HW1_WORLD_H

#include <fstream>
#include <sstream>
#include <vector>
#include "Utilities.h"
#include "SARS_CoV_2.h"
#include "RCPtr.h"
#include "XBB.h"
#include "BQ.h"
#include "CH.h"
#include <random>
#include <algorithm>

using namespace std;

// print the end of the game
void print(vector<RCPtr<SARS_CoV_2>>& viruses, const vector<char> &bestDNA,const vector<RCPtr<SARS_CoV_2>>& parents){
    for (RCPtr<SARS_CoV_2> &virus : viruses){
        virus->print();
    }
    cout << endl;

    for (const RCPtr<SARS_CoV_2> &virus : parents){
        for (char c : virus->getDNA()){
            cout << c << " ";
        }
        cout << virus.use_count()-1 << endl;
    }
    cout << endl;

    for (char c : bestDNA){
        cout << c << " ";
    }
}

// update each virus same as ask
void personalUpdates(vector<RCPtr<SARS_CoV_2>>& viruses){
    for (RCPtr<SARS_CoV_2> &virus : viruses){
        virus->personalUpdate();
    }
}

// update who's the virus with the best ratio
void bestVirusUpdate(float &bestRatio,  vector<char> &bestDNA, const vector<RCPtr<SARS_CoV_2>>& viruses,vector<char> &target, int dimension){
    for (const RCPtr<SARS_CoV_2> &virus: viruses){
        if (virus->ratioOfHit(target,dimension) > bestRatio){
            bestRatio = virus->ratioOfHit(target,dimension);
            bestDNA = virus->getDNA();
        }
    }
}

// update the crew same as ask
void crewUpdate(const vector<RCPtr<SARS_CoV_2>> &parents, vector<RCPtr<SARS_CoV_2>> &current,const vector<char> &target){
    int x = rand()% parents.size();
    int y = rand()% parents.size();
    while (x == y){
        y = rand()% parents.size();
    }

    int s = rand()% (current[0]->getDNA().size()-4) + 2;
    int t = rand()% (current[0]->getDNA().size()-4) + 3;
    while (s == t){
        t = rand()% (current[0]->getDNA().size()-4) + 3;
    }
    if (t < s)
        std::swap(s,t);

    vector<char> DNAx = parents[x]->getDNA();
    vector<char> DNAy = parents[y]->getDNA();

    for (int i = s; i <= t; ++i) {
        std::swap(DNAx[i],DNAy[i]);
    }
    std::sort(current.begin(), current.end(),
          [&target](const RCPtr<SARS_CoV_2> &v1, const RCPtr<SARS_CoV_2> &v2) {
              return v1->ratioOfHit(target,target.size()) <= v2->ratioOfHit(target,target.size());
  });

    switch (parents[x]->getDNA()[0]) {
        case 'x':
            current[0] = new XBB(DNAx,parents[x]);
            break;
        case 'b':
            current[0] = new BQ(DNAx,parents[x]);
            break;
        case 'c':
            current[0] = new CH(DNAx,parents[x]);
            break;
    }
    switch (parents[y]->getDNA()[0]) {
        case 'x':
            current[1] = new XBB(DNAx,parents[y]);
            break;
        case 'b':
            current[1] = new BQ(DNAx,parents[y]);
            break;
        case 'c':
            current[1] = new CH(DNAx,parents[y]);
            break;
    }
}

// run to simulate
void play(const string& config, const string& init){

    //read the files
    int dimension = -1;
    int time = 0;
    vector<char> target = readConfig(config, dimension,time);

    int sumOfVirus = -1; // readInit() fix it to the correct number;
    vector<vector<char>> DNAs = readInit(init, sumOfVirus, dimension);

    vector<RCPtr<SARS_CoV_2>> parents;

    for (vector<char> &v : DNAs) {
        switch (v[0]) {
            case 'x':
                parents.push_back(new XBB(v, nullptr));
                break;
            case 'b':
                parents.push_back(new BQ(v, nullptr));
                break;
            case 'c':
                parents.push_back(new CH(v, nullptr));
                break;
        }
    }

    vector<RCPtr<SARS_CoV_2>> currents;

    for (RCPtr<SARS_CoV_2> &v : parents){
        switch (v->getDNA()[0]) {
            case 'x':
                currents.push_back(new XBB(v->getDNA(),v));
                break;
            case 'b':
                currents.push_back(new BQ(v->getDNA(),v));
                break;
            case 'c':
                currents.push_back(new CH(v->getDNA(),v));
                break;
        }
    }
    vector<char> bestDNA;
    float bestRatio = 0;

    bestVirusUpdate(bestRatio, bestDNA,currents , target,dimension);
    while (time-- != 0 && bestRatio != 1.0){
        crewUpdate(parents,currents,target);
        personalUpdates(currents);
        bestVirusUpdate(bestRatio, bestDNA,currents , target,dimension);
    }

//    // print as ask
    print(currents,bestDNA,parents);
}


#endif //HW1_WORLD_H
