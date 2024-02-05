#include <iostream>
#include "simulation.h"

using namespace std;


int main(int argc, char* argv[]) {
    srand(time(nullptr));
    try {
        if (argc != 3){
            throw invalid_argument("usage number of argument");
        }
        simulation s = simulation(argv[1],argv[2]);
        s.play();
    }
    catch (exception& error) {
        cout << error.what() << endl;
    }
    return 0;
}
