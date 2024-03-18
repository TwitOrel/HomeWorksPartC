//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_OMSTERDAM_H
#define EX_2_OMSTERDAM_H

#include <string>
#include "Graph.h"
#include "Utilities.h"
#include "Station.h"
#include "Intercity.h"
#include "Centraal.h"
#include "Stad.h"
#include "Vehicles.h"
#include "Bus.h"
#include "Rail.h"
#include "Tram.h"
#include "Sprinter.h"

using namespace std;

class Omsterdam {
private:
    static string outFileName;
    Graph graph;

    // using for load file 1
    void readFile(const string &filename);

    // using for outbound 2
    void outbound(const string &source)const;

    // using for inbound 3
    void inbound(const string &target)const;

    // using for uniExpress 4
    void uniExpress(const string &source, const string &target)const;

    // using for multiExpress 5
    void multiExpress(const string &source, const string &target)const;

    // using for viaExpress 6
    void viaExpress(const string &source, const string &transit, const string &target)const;

    // using for print 7
    void print()const;

    //read the file and init by him
    void readAndInitFile(const string &filename, const vector<string> &vehicleName, const vector<string> &stationsName,const string &nameFile);

    // check if graph have there is station named "..."
    bool containsStation(const string &station)const;

public:
    Omsterdam();

    Omsterdam(const Omsterdam& o);

    Omsterdam& operator=(const Omsterdam& o);

    Omsterdam(Omsterdam && o) noexcept ;

    Omsterdam& operator=(Omsterdam&& o) noexcept ;

    ~Omsterdam();

    // reading files as start the program
    void readFiles(int argc, char *argv[]);

    // run time
    void Simulate();

};

#endif //EX_2_OMSTERDAM_H