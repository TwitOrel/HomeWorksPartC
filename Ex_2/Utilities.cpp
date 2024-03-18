//
// Created by Orel on 03/03/2024.
//

#include <vector>
#include "Utilities.h"

// Function to find substring in a string
bool findSubstring(const string &str, const string &substr) {
    int strLength = str.length();
    int subLength = substr.length();

    for (int i = 0; i <= strLength - subLength; ++i) {
        int j;
        for (j = 0; j < subLength; ++j) {
            if (str[i + j] != substr[j]) {
                break; // Break out of the inner loop if characters don't match
            }
        }
        if (j == subLength) {
            return true; // Return the true where the substring starts
        }
    }

    return false; // Return false if the substring is not found
}

string extractSubstring(const string &filename, const vector<string> &types) {
    for (const auto &type: types) {
        size_t pos = filename.find(type);
        if (pos != string::npos) {
            return filename.substr(pos, type.length());
        }
    }
    return ""; // Return empty string if no match is found
}

bool isValidString(const std::string &str) {
    if (str.size() > 16) {
        return false; // String size is 16 or more
    }

    for (char c: str) {
        if (c == ' ') {
            return false; // String contains space
        }
    }

    return true; // String is valid
}

map<string, int> &mapSimulate(map<string, int> &map) {
    map.insert({"load", 1});
    map.insert({"outbound", 2});
    map.insert({"inbound", 3});
    map.insert({"uniExpress", 4});
    map.insert({"multiExpress", 5});
    map.insert({"viaExpress", 6});
    map.insert({"print", 7});
    map.insert({"exit", 8});

    return map;
}
