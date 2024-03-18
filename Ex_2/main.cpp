#include <iostream>
#include "Omsterdam.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        Omsterdam orel = Omsterdam();
        orel.readFiles(argc, argv);
        orel.Simulate();
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}