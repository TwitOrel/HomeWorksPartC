//
// Created by Orel on 03/03/2024.
//

#ifndef EX_2_UTILITIES_H
#define EX_2_UTILITIES_H

#include <string>
#include <map>

using namespace std;

// check if substr in str
bool findSubstring(const string& str, const string& substr);

// return the substring from the filename that contain in the vector
string extractSubstring(const string& filename, const vector<string>& types);

// using to check if name stations is correct
bool isValidString(const std::string& str);

// return map for the simulate for the switch case
map<string ,int>& mapSimulate(map<string,int> &map);


#endif //EX_2_UTILITIES_H
