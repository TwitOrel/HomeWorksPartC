//
// Created by Orel on 21/02/2024.
//

#include "Omsterdam.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

Omsterdam::Omsterdam(): graph({}) {}

Omsterdam::Omsterdam(const Omsterdam &o) = default;

Omsterdam &Omsterdam::operator=(const Omsterdam &o) {
    if (this == &o){
        return *this;
    }
    this->graph = o.graph;
    return *this;
}

Omsterdam::Omsterdam(Omsterdam &&o) noexcept:graph(std::move(o.graph)) {}

Omsterdam &Omsterdam::operator=(Omsterdam &&o) noexcept {
    if (this == &o){
        return *this;
    }
    this->graph = std::move(o.graph);
    return *this;
}

Omsterdam::~Omsterdam() = default;


void Omsterdam::readAndInitFile(const string &filename, const vector<string> &vehiclesNames, const vector<string> &stationsName,const string &nameFile) {
    if (filename.empty()){
        throw invalid_argument("No matching TypeNameFile to init {-c, -o, bus, sprinter, rail, tram}");
    }

    ifstream inputFile(filename);
    if (!inputFile) {
        throw invalid_argument("Error: Unable to open input file: " + filename);
    }
    if (nameFile == "-c") { // config
        string line;
        while (getline(inputFile,line)){
            stringstream ss(line);
            string typeVehicle, dis;
            int distance;
            if (!(ss >> typeVehicle >> dis)){
                throw runtime_error("Error: Invalid format with config file");
            }
            string remain;
            if (ss >> remain){
                throw runtime_error("Error: Invalid format with config file");
            }

            distance = stoi(dis);
            typeVehicle = extractSubstring(typeVehicle, vehiclesNames);

            if (typeVehicle == "bus"){
                Bus::setExchange(distance);
            }
            else if (filename == "rail"){
                Rail::setExchange(distance);
            }
            else if (filename == "sprinter"){
                Sprinter::setExchange(distance);
            }
            else{
                Tram::setExchange(distance);
            }
        }
    }

    else if (nameFile == "bus"){
        string line;
        while (getline(inputFile,line)){
            stringstream ss(line);
            string from, to, dis;
            int distance;
            if (!(ss >> from >> to >> dis)){
                throw runtime_error("Error: Invalid format with bus file");
            }
            string remain;
            if (ss >> remain){
                throw runtime_error("Error: Invalid format with bus file");
            }
            if (!isValidString(from)){
                throw runtime_error("Error: bus file stations " + from + " invalid");
            }
            if (!isValidString(to)){
                throw runtime_error("Error: bus file stations " + to + " invalid");
            }

            distance = stoi(dis);
            string subFrom = extractSubstring(from, stationsName);
            string subTo = extractSubstring(to, stationsName);
            shared_ptr<Station> f;
            shared_ptr<Station> t;
            if (subFrom == "CS"){
                f = make_shared<Centraal>(from);
            }
            else if (subFrom == "IC"){
                f = make_shared<Intercity>(from);
            }
            else{
                f = make_shared<Stad>(from);
            }

            if (subTo == "CS"){
                t = make_shared<Centraal>(to);
            }
            else if (subTo == "IC"){
                t = make_shared<Intercity>(to);
            }
            else{
                t = make_shared<Stad>(to);
            }
            shared_ptr<Vehicles> b = make_shared<Bus>(distance);
            this->graph.putEdge(f,t,b);
        }
    }

    else if (nameFile == "rail"){
        string line;
        while (getline(inputFile,line)) {
            stringstream ss(line);
            string from, to, dis;
            int distance;
            if (!(ss >> from >> to >> dis)) {
                throw runtime_error("Error: Invalid format with rail file");
            }
            string remain;
            if (ss >> remain){
                throw runtime_error("Error: Invalid format with rail file");
            }
            if (!isValidString(from)){
                throw runtime_error("Error: rail file stations " + from + " invalid");
            }
            if (!isValidString(to)){
                throw runtime_error("Error: rail file stations " + to + " invalid");
            }

            distance = stoi(dis);
            string subFrom = extractSubstring(from, stationsName);
            string subTo = extractSubstring(to, stationsName);
            shared_ptr<Station> f;
            shared_ptr<Station> t;
            if (subFrom == "CS") {
                f = make_shared<Centraal>(from);
            } else if (subFrom == "IC") {
                f = make_shared<Intercity>(from);
            } else {
                f = make_shared<Stad>(from);
            }

            if (subTo == "CS") {
                t = make_shared<Centraal>(to);
            } else if (subTo == "IC") {
                t = make_shared<Intercity>(to);
            } else {
                t = make_shared<Stad>(to);
            }
            shared_ptr<Vehicles> b = make_shared<Rail>(distance);
            this->graph.putEdge(f, t, b);
        }
    }

    else if (nameFile == "sprinter"){
        string line;
        while (getline(inputFile,line)) {
            stringstream ss(line);
            string from, to, dis;
            int distance;
            if (!(ss >> from >> to >> dis)) {
                throw runtime_error("Error: Invalid format with sprinter file");
            }
            string remain;
            if (ss >> remain){
                throw runtime_error("Error: Invalid format with sprinter file");
            }
            if (!isValidString(from)){
                throw runtime_error("Error: sprinter file stations " + from + " invalid");
            }
            if (!isValidString(to)){
                throw runtime_error("Error: sprinter file stations " + to + " invalid");
            }

            distance = stoi(dis);
            string subFrom = extractSubstring(from, stationsName);
            string subTo = extractSubstring(to, stationsName);
            shared_ptr<Station> f;
            shared_ptr<Station> t;
            if (subFrom == "CS") {
                f = make_shared<Centraal>(from);
            } else if (subFrom == "IC") {
                f = make_shared<Intercity>(from);
            } else {
                f = make_shared<Stad>(from);
            }

            if (subTo == "CS") {
                t = make_shared<Centraal>(to);
            } else if (subTo == "IC") {
                t = make_shared<Intercity>(to);
            } else {
                t = make_shared<Stad>(to);
            }
            shared_ptr<Vehicles> b = make_shared<Sprinter>(distance);
            this->graph.putEdge(f, t, b);
        }
    }

    else if(nameFile == "tram"){
        string line;
        while (getline(inputFile,line)) {
            stringstream ss(line);
            string from, to, dis;
            int distance;
            if (!(ss >> from >> to >> dis)) {
                throw runtime_error("Error: Invalid format with tram file");
            }
            string remain;
            if (ss >> remain){
                throw runtime_error("Error: Invalid format with tram file");
            }
            if (!isValidString(from)){
                throw runtime_error("Error: tram file stations " + from + " invalid");
            }
            if (!isValidString(to)){
                throw runtime_error("Error: tram file stations " + to + " invalid");
            }

            distance = stoi(dis);
            string subFrom = extractSubstring(from, stationsName);
            string subTo = extractSubstring(to, stationsName);
            shared_ptr<Station> f;
            shared_ptr<Station> t;
            if (subFrom == "CS") {
                f = make_shared<Centraal>(from);
            } else if (subFrom == "IC") {
                f = make_shared<Intercity>(from);
            } else {
                f = make_shared<Stad>(from);
            }

            if (subTo == "CS") {
                t = make_shared<Centraal>(to);
            } else if (subTo == "IC") {
                t = make_shared<Intercity>(to);
            } else {
                t = make_shared<Stad>(to);
            }
            shared_ptr<Vehicles> b = make_shared<Tram>(distance);
            this->graph.putEdge(f, t, b);
        }
    }

    else{
        throw invalid_argument(" ERROR opening the specified file. ");
    }

    inputFile.close();
}

void Omsterdam::readFiles(int argc, char *argv[]) {
    // check if you have at least 2 files
    if (argc < 2){
        throw invalid_argument(string("ERROR: ") + argv[0] + " program can't run with less than 2 files");
    }
    vector<string> typesFilesName{"-c", "-o", "bus", "rail", "tram", "sprinter"};
    vector<string> vehicleName{"bus", "rail", "tram", "sprinter"};
    vector<string> stationsName{"IC", "CS"};

    // opening the files and use them
    for (int i = 1; i < argc; ++i) {
        string filename = argv[i];
        string nameFile = extractSubstring(filename, typesFilesName);


        if (nameFile == "-o"){
            Omsterdam::outFileName = nameFile;
        }
        readAndInitFile(filename, vehicleName, stationsName,nameFile);
    }
}

void Omsterdam::readFile(const string &filename){
    try {
    vector<string> typesFilesName{"-c", "bus", "rail", "tram", "sprinter"};
    vector<string> vehicleName{"bus", "rail", "tram", "sprinter"};
    vector<string> stationsName{"IC", "CS"};

    string nameFile = extractSubstring(filename, typesFilesName);
    readAndInitFile(filename,vehicleName,stationsName,nameFile);
    }
    catch (exception &e){
        cout << "ERROR opening the specified file. \n";
    }
}

bool Omsterdam::containsStation(const string &station)const {
    if (!this->graph.containsVertex(station)) {
        cout << station << " does not exist in the current network \n";
        return false;
    }
    return true;
}

void Omsterdam::outbound(const string &source)const {
    if (!containsStation(source)) return;
    shared_ptr<Station> from = graph.getVertex(source);

    vector<shared_ptr<Station>> busRun = Graph::BFS(graph,from,'b');
    vector<shared_ptr<Station>> tramRun = Graph::BFS(graph,from,'t');
    vector<shared_ptr<Station>> sprinterRun = Graph::BFS(graph,from,'s');
    vector<shared_ptr<Station>> railRun = Graph::BFS(graph,from,'r');


    if (busRun.size() + railRun.size() + tramRun.size() + sprinterRun.size() == 0){
        cout << source << " : no outbound travel" << endl;
    }
    else{
        if (busRun.empty()){
            cout << "bus: no outbound travel" << endl;
        }
        else{
            cout << "bus: ";
            for (auto &s : busRun){
                cout << s->getName() << " ";
            }
            cout << endl;
        }
        if (tramRun.empty()){
            cout << "tram: no outbound travel" << endl;
        }
        else{
            cout << "tram: ";
            for (auto &s : tramRun){
                cout << s->getName() << " ";
            }
            cout << endl;

        }
        if (sprinterRun.empty()){
            cout << "sprinter: no outbound travel" << endl;
        }
        else{
            cout << "sprinter: ";
            for (auto &s : sprinterRun){
                cout << s->getName() << " ";
            }
            cout << endl;

        }
        if (railRun.empty()){
            cout << "rail: no outbound travel" << endl;
        }
        else{
            cout << "rail: ";
            for (auto &s : railRun){
                cout << s->getName() << " ";
            }
            cout << endl;

        }

    }
}

void Omsterdam::inbound(const string &target)const {
    if (!containsStation(target)) return;

    shared_ptr<Station> from = graph.getVertex(target);
    Graph tGraph = this->graph.transpose();

    vector<shared_ptr<Station>> busRun = Graph::BFS(tGraph, from, 'b');
    vector<shared_ptr<Station>> tramRun = Graph::BFS(tGraph, from, 't');
    vector<shared_ptr<Station>> sprinterRun = Graph::BFS(tGraph, from, 's');
    vector<shared_ptr<Station>> railRun = Graph::BFS(tGraph, from, 'r');

    if (busRun.size() + railRun.size() + tramRun.size() + sprinterRun.size() == 0){
        cout << target << " : no inbound travel" << endl;
    }
    else{
        if (busRun.empty()){
            cout << "bus: no inbound travel" << endl;
        }
        else{
            cout << "bus: ";
            for (auto &s : busRun){
                cout << s->getName() << " ";
            }
            cout << endl;
        }
        if (tramRun.empty()){
            cout << "tram: no inbound travel" << endl;
        }
        else{
            cout << "tram: ";
            for (auto &s : tramRun){
                cout << s->getName() << " ";
            }
            cout << endl;
        }
        if (sprinterRun.empty()){
            cout << "sprinter: no inbound travel" << endl;
        }
        else{
            cout << "sprinter: ";
            for (auto &s : sprinterRun){
                cout << s->getName() << " ";
            }
            cout << endl;
        }
        if (railRun.empty()){
            cout << "rail: no inbound travel" << endl;
        }
        else{
            cout << "rail: ";
            for (auto &s : railRun){
                cout << s->getName() << " ";
            }
            cout << endl;
        }
    }
}

void Omsterdam::uniExpress(const string& source, const string& target)const {
    if (!containsStation(source)) return;
    if (!containsStation(target)) return;

    shared_ptr<Station> from = graph.getVertex(source);
    shared_ptr<Station> to = graph.getVertex(target);

    int busRun = Graph::Dijkstra(graph,from,to,'b');
    int tramRun = Graph::Dijkstra(graph,from,to,'t');
    int sprinterRun = Graph::Dijkstra(graph,from,to,'s');
    int railRun = Graph::Dijkstra(graph,from,to,'r');

    cout << "bus: " << ((busRun == -1)? "route unavailable\n" : to_string(busRun) + "\n");
    cout << "tram: " << ((tramRun == -1)? "route unavailable\n" : to_string(tramRun) + "\n");
    cout << "sprinter: " << ((sprinterRun == -1)? "route unavailable\n" : to_string(sprinterRun) + "\n");
    cout << "rail: " << ((railRun == -1)? "route unavailable\n" : to_string(railRun) + "\n");
}

void Omsterdam::multiExpress(const string &source, const string &target)const {
    if (!containsStation(source)) return;
    if (!containsStation(target)) return;

    shared_ptr<Station> from = graph.getVertex(source);
    shared_ptr<Station> to = graph.getVertex(target);

    // dif is only for run the function (no used)
    map<char,int> dif;
    dif['b'] = 0;
    dif['r'] = 0;
    dif['s'] = 0;
    dif['t'] = 0;
    int express = Graph::multiDijkstra(graph, from, to, dif);

    cout << ((express == -1)? "route unavailable from " + source + " to " + target + "\n" : "from " + source + " to " + target + " route = " + to_string(express) + "\n");
}

void Omsterdam::viaExpress(const string& source, const string& transit, const string& target)const {
    if (!containsStation(source)) return;
    if (!containsStation(transit)) return;
    if (!containsStation(target)) return;

    shared_ptr<Station> from = graph.getVertex(source);
    shared_ptr<Station> between = graph.getVertex(transit);
    shared_ptr<Station> to = graph.getVertex(target);

    int express = Graph::viaDijkstra(graph, from, to, between);
    cout << ((express == -1)? "route unavailable from " + source + " between " + transit + " to " + target + "\n" : "from " + source + " between " + transit + " to " + target + " route = " + to_string(express) + "\n");
}

void Omsterdam::print()const {
    this->graph.printGraph(Omsterdam::outFileName);
}

void Omsterdam::Simulate() {
    map<string, int> calls;
    calls = mapSimulate(calls);
    cout << "All set." << endl;
    string line;
        while (true) {
            try {
            cout << "input:";
            getline(cin, line);
            stringstream ss(line);
            string command;
            ss >> command;

            string from;
            string to;
            string transit;

            string remain;
            int intCommand = calls[command];

            switch (intCommand) {
                case 1:     // load
                    ss >> command;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command load");
                    }
                    readFile(command);
                    break;

                case 2:     // outbound
                    ss >> from;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command outbound");
                    }
                    outbound(from);
                    break;

                case 3:     // inbound
                    ss >> to;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command inbound");
                    }
                    inbound(to);
                    break;

                case 4:     //  uniExpress
                    ss >> from >> to;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command inbound");
                    }
                    uniExpress(from, to);
                    break;

                case 5:     // multiExpress
                    ss >> from >> to;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command inbound");
                    }
                    multiExpress(from, to);
                    break;

                case 6:     // viaExpress
                    ss >> from >> transit >> to;
                    if (ss >> remain) {
                        throw logic_error("Error: Invalid format with command inbound");
                    }
                    viaExpress(from, transit, to);
                    break;
                case 7:     // print
                    print();
                    break;
                case 8:     // exit
                    return;
                default:
                    cout << "Invalid request: pls choose again" << endl;
            }
        }
        catch (logic_error &e) {
            cout << e.what();
        }
    }
}

string Omsterdam::outFileName = "output.dat";
