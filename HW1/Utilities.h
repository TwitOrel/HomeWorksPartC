//
// Created by Orel on 30/01/2024.
//

#ifndef HW1_UTILITIES_H
#define HW1_UTILITIES_H
using namespace std;
#include <fstream>
#include <sstream>
#include "Utilities.h"


bool isNumeric (const string& line);

// read from line the DNA and add it to virus sv
void initVirus(const string& line, int dim, vector<char> &sv);

// read the DNA's from the initFile and add it to viruses
void initViruses(ifstream &initFile, int dimension, int sumOfViruses, vector<vector<char>> &viruses);

vector<vector<char>> readInit(const string& init, int &sumOfVirus, const int &dimension);

// read from line the DNA and add it to virus target
void initStringTarget(const string& line, int dim, vector<char> &st);

vector<char> readConfig(const string& config, int &dimension, int &time);

#endif //HW1_UTILITIES_H
