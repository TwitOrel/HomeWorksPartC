//
// Created by Orel on 05/02/2024.
//

#include "simulation.h"

simulation::simulation(const std::string &config, const std::string &init) {
    //read the files
    target = readConfig(config, dimension,time);
    DNAs = readInit(init, sumOfVirus, dimension);

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
}

void simulation::print() {
    for (RCPtr<SARS_CoV_2> &virus : currents){
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

void simulation::personalUpdates() {
    for (RCPtr<SARS_CoV_2> &virus : currents){
        virus->personalUpdate();
    }
}

void simulation::bestVirusUpdate() {
    for (const RCPtr<SARS_CoV_2> &virus: currents){
        if (virus->ratioOfHit(target,dimension) > bestRatio){
            bestRatio = virus->ratioOfHit(target,dimension);
            bestDNA = virus->getDNA();
        }
    }
}

void simulation::crewUpdate() {
    int x = rand()% (int)parents.size();
    int y = rand()% (int)parents.size();
    while (x == y){
        y = rand()% (int)parents.size();
    }

    int s = rand()% (int)(currents[0]->getDNA().size()-4) + 2;
    int t = rand()% (int)(currents[0]->getDNA().size()-4) + 3;
    while (s == t){
        t = rand()% (int)(currents[0]->getDNA().size()-4) + 3;
    }
    if (t < s)
        std::swap(s,t);

    vector<char> DNAx = parents[x]->getDNA();
    vector<char> DNAy = parents[y]->getDNA();

    for (int i = s; i <= t; ++i) {
        std::swap(DNAx[i],DNAy[i]);
    }
    std::sort(currents.begin(), currents.end(),
              [&](const RCPtr<SARS_CoV_2> &v1, const RCPtr<SARS_CoV_2> &v2) {
                  return v1->ratioOfHit(target,(int)target.size()) <= v2->ratioOfHit(target,(int)target.size());
              });

    switch (parents[x]->getDNA()[0]) {
        case 'x':
            currents[0] = new XBB(DNAx,parents[x]);
            break;
        case 'b':
            currents[0] = new BQ(DNAx,parents[x]);
            break;
        case 'c':
            currents[0] = new CH(DNAx,parents[x]);
            break;
    }
    switch (parents[y]->getDNA()[0]) {
        case 'x':
            currents[1] = new XBB(DNAx,parents[y]);
            break;
        case 'b':
            currents[1] = new BQ(DNAx,parents[y]);
            break;
        case 'c':
            currents[1] = new CH(DNAx,parents[y]);
            break;
    }
}

void simulation::play() {
    bestVirusUpdate();
    while (time-- != 0 && bestRatio != 1.0){
        crewUpdate();
        personalUpdates();
        bestVirusUpdate();
    }
//    // print as ask
    print();
}








