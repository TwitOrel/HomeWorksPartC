//
// Created by Orel on 05/02/2024.
//

#include "simulation.h"

bool isNumeric (const string& line) {
    for (char c: line) {
        if (c > 57 || c < 46) {
            return false;
        }
    }
    return true;
}

void initVirus(const string& line, int dim, vector<char> &sv){

    stringstream ss(line);

    // Read each nucleotide separated by spaces and store them in the vector
    char nucleotide;
    while (ss >> nucleotide) {
        sv.push_back(nucleotide);
    }
    if ((int)sv.size() != dim){
        throw invalid_argument("ERROR: Invalid input.");
    }

    for (int i = 0; i < (int)sv.size(); ++i) {
        if (i == 0){
            if (!(sv[i] == 'x' || sv[i] == 'b' || sv[i] == 'c'))
                throw invalid_argument("ERROR: Invalid input, wrong type {x,b,c}");
        }
        else{
            if (!(sv[i] == 'A' || sv[i] == 'T' || sv[i] == 'G' || sv[i] == 'C'))
                throw invalid_argument("ERROR: Invalid input, wrong type {A,T,G,C}");
        }
    }
}

void initViruses(ifstream &initFile, int dimension, int sumOfViruses, vector<vector<char>> &viruses){
    string line;
    while (getline(initFile,line)){
        sumOfViruses--;
        vector<char> i;
        initVirus(line,dimension+1,i);
        viruses.push_back(i);
    }
    if (sumOfViruses != 0){
        throw invalid_argument("ERROR: Invalid input with sum of viruses.");
    }

}

vector<vector<char>> readInit(const string& init, int &sumOfVirus, const int &dimension){

    vector<vector<char>> viruses;

    // create file Stream and check it is not null
    ifstream initFile(init);
    if (!initFile) {
        throw  invalid_argument("Failed to open the file.") ;
    }
    string line;
    getline(initFile, line);
    // check if there is no char or even space
    if (!isNumeric(line)){
        throw invalid_argument("ERROR: Invalid input sumOfVirus.");
    }

    sumOfVirus = stoi(line);
    if (sumOfVirus < 4 || dimension > 500){
        throw invalid_argument("ERROR: Invalid input with sumOfVirus.");
    }

    initViruses(initFile,dimension,sumOfVirus,viruses);

    return viruses;
}

void initStringTarget(const string& line, int dim, vector<char> &st){

    stringstream ss(line);

    // Read each nucleotide separated by spaces and store them in the vector
    char nucleotide;
    while (ss >> nucleotide) {
        st.push_back(nucleotide);
    }
    if ((int)st.size() != dim){
        throw invalid_argument("ERROR: Invalid input.");
    }
    for(char c: st){
        if (!(c == 'A' || c == 'T' || c == 'G' || c == 'C'))
            throw invalid_argument("ERROR: Invalid input, wrong type {A,T,G,C}");
    }
}

vector<char> readConfig(const string& config, int &dimension, int &time){

    // create file Stream and check it is not null
    ifstream configFile(config);
    if (!configFile) {
        throw  invalid_argument("Failed to open the file.") ;
    }

    string line;
    getline(configFile,line);

    // check if there is no char or even space
    if (!isNumeric(line)){
        throw invalid_argument("ERROR: Invalid input with dimension.");
    }

    dimension = stoi(line);
    if (dimension < 8 || dimension > 1024){
        throw invalid_argument("ERROR: Invalid input with dimension.");
    }

    getline(configFile,line);
    vector<char> StringTarget;
    initStringTarget(line,dimension,StringTarget);


    getline(configFile,line);
    // check if there is no char or even space
    if (!isNumeric(line)){
        throw invalid_argument("ERROR: Invalid input with time.");
    }
    time = stoi(line);
    if (time < 0 || time > 1000000){
        throw invalid_argument("ERROR: Invalid input with time.");
    }
    return StringTarget;
}