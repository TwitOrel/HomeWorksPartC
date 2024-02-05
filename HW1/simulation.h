//
// Created by Orel on 05/02/2024.
//

#ifndef HW1_SIMULATION_H
#define HW1_SIMULATION_H
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

class simulation{
private:
    // fields
    int dimension = -1;
    int time = 0;
    int sumOfVirus = -1;
    float bestRatio = 0;
    vector<char> bestDNA;
    vector<vector<char>> DNAs;
    vector<char> target;
    vector<RCPtr<SARS_CoV_2>> parents;
    vector<RCPtr<SARS_CoV_2>> currents;

    // print the end of the game
    void print();

    // update each virus same as ask
    void personalUpdates();

    // update who's the virus with the best ratio
    void bestVirusUpdate();

    // update the crew same as ask
    void crewUpdate();

public:
    simulation(const string& config, const string& init);

    // run to simulate
    void play();
    };

#endif //HW1_SIMULATION_H