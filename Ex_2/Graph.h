//
// Created by Orel on 21/02/2024.
//

#ifndef EX_2_GRAPH_H
#define EX_2_GRAPH_H
using namespace std;

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include "vector"
#include <memory>
#include <map>
#include <set>
#include <queue>
#include <limits>
#include "Station.h"
#include "Vehicles.h"

class Graph {
private:
    static void checkVertex(const Graph &graph, const shared_ptr<Station> &station) {
        if (!graph.containsVertex(station)) {
            throw logic_error(station->getName() + " does not exist in the current network \n");
        }
    }

    class comparator {
    public:
        bool operator()(const shared_ptr<Station> &a, const shared_ptr<Station> &b) const {
            return *a < *b;
        }
    };

    class Edge {
    public:
        // from
        shared_ptr<Station> u;
        // to
        shared_ptr<Station> v;
        shared_ptr<Vehicles> label;

        Edge(const shared_ptr<Station> &u, const shared_ptr<Station> &v, const shared_ptr<Vehicles> &label) {
            this->u = u;
            this->v = v;
            this->label = label;
        }
    };


    map<shared_ptr<Station>, vector<Edge>, comparator> vertexToIncidences;
public:
    Graph()= default;

    Graph(const Graph& g) = default;

    Graph& operator=(const Graph &g){
        if (this == &g){
            return *this;
        }
        this->vertexToIncidences = g.vertexToIncidences;
        return *this;
    }

    Graph(Graph &&g) noexcept :vertexToIncidences(std::move(g.vertexToIncidences)){}

    Graph& operator=(Graph &&g) noexcept {
        if (this == &g){
            return *this;
        }
        this->vertexToIncidences = std::move(g.vertexToIncidences);
        return *this;
    }

    ~Graph() = default;

    void addVertex(const shared_ptr<Station> &v) {
        if (!containsVertex(v)) {
            vertexToIncidences[v] = vector<Edge>();
        }
    }

    bool containsVertex(const shared_ptr<Station> &v) const {
        return vertexToIncidences.find(v) != vertexToIncidences.end();
    }

    bool containsVertex(const string &name)const noexcept{
        for (auto &it: this->vertexToIncidences) {
            if (it.first->getName() == name) {
                return true;
            }
        }
        return false;
    }

    shared_ptr<Station> getVertex(const string &name)const {
        for (auto &it: this->vertexToIncidences) {
            if (it.first->getName() == name) {
                return it.first;
            }
        }
        return nullptr;
    }

    // if u == v its edge to my self
    void putEdge(const shared_ptr<Station> &u, const shared_ptr<Station> &v, const shared_ptr<Vehicles> &label) {
        addVertex(u);
        addVertex(v);
        // check if the edge exist
        vector<Edge> &edges = vertexToIncidences[u];
        for (Edge &e: edges) {
            if (e.label->getType() == label->getType() && *(e.v) == *v) {
                e.label->setDistance(label->getDistance());
                return;
            }
        }

        // the edge not exist, addVertex it
        edges.emplace_back(u, v, label);
    }

    // using for making copy graph but the direction of the edges are reversed
    Graph transpose()const noexcept{
        Graph ret{};
        for (const auto &v: vertexToIncidences) {
            ret.addVertex(v.first);
        }
        for (const auto &v: vertexToIncidences) {
            for (const auto &edge: v.second) {
                ret.putEdge(edge.v, edge.u, edge.label);
            }
        }
        return ret;
    }

    // print every vertex with the edges from him with weight and type Vehicle to stream
    void printGraph(const string &fileName) const {
        // create stream to write to a file
        ofstream outputFile = ofstream(fileName);

        if (!outputFile) {
            std::cerr << "Error: Unable to open output file!" << std::endl;
            return;
        }

        for (const auto &vertex: vertexToIncidences) {
            outputFile << *vertex.first << " ";
            vector<Edge> tmp = vertex.second;
            vector<Edge>::iterator itEdge;
            for (const auto &Edge: tmp) {
                outputFile << "[" << "from " << Edge.u->getName() << ", to " << Edge.v->getName() << " (by '"
                           << Edge.label->getType() << "') = " << Edge.label->getDistance() << "] ";
            }
            outputFile << '\n';
        }
        outputFile.close();
    }

    // return vector<Station> that can show to where can I go (only on one type Vehicle)
    static vector<shared_ptr<Station>> BFS(const Graph &graph, const shared_ptr<Station> &from, char type) {
        checkVertex(graph, from);
        // set for the accessible stations
        vector<shared_ptr<Station>> accessible;

        // set for the visited vertexes
        set<shared_ptr<Station>> visited;

        // set to the algorithm
        queue<shared_ptr<Station>> tor;

        // Enqueue the first station
        tor.push(from);
        visited.insert(from);

        // start the party
        while (!tor.empty()) {
            auto currentS = tor.front();
            tor.pop();

            // check for all edges from current to...
            for (const auto &edge: graph.vertexToIncidences.at(currentS)) {

                if (edge.label->getType() == type) {
                    shared_ptr<Station> des = edge.v;
                    if (visited.find(des) == visited.end()) {
                        visited.insert(des);
                        tor.push(des);
                        accessible.push_back(des);
                    }
                }
            }
        }
        return accessible;
    }

    // return the shortest length from u to v (only on one type Vehicle)
    static int Dijkstra(const Graph &graph, const shared_ptr<Station> &from, const shared_ptr<Station> &to, char type) {
        checkVertex(graph, from);
        checkVertex(graph, to);

        if (!graph.containsVertex(from)) {
            throw logic_error(from->getName() + " does not exist in the current network \n");
        }

        // set for the visited vertexes
        set<shared_ptr<Station>, comparator> visited;

        //create map to store the distance between from to each vertex
        map<shared_ptr<Station>, int, comparator> distance;

        // init infinity for the algorithm
        for (const auto &vertex: graph.vertexToIncidences) {
            distance[vertex.first] = numeric_limits<int>::max();
        }
        distance[from] = 0;
        priority_queue<pair<int, shared_ptr<Station>>, vector<pair<int, shared_ptr<Station>>>, greater<pair<int, shared_ptr<Station>>>> pq;
        pq.emplace(0, from);
        while (!pq.empty()) {
            shared_ptr<Station> current = pq.top().second;
            pq.pop();

            visited.insert(current);

            for (const auto &edge: graph.vertexToIncidences.at(current)) {
                if (edge.label->getType() == type) {
                    shared_ptr<Station> neighbor = edge.v;

                    int weight = edge.label->getDistance();
                    if (!(*edge.v == *to)) {
                        weight += edge.label->getExchange();
                    }

                    if ((distance[current] + weight) < distance[neighbor]) {
                        distance[neighbor] = (distance[current] + weight);
                        pq.emplace(distance[neighbor], neighbor);
                    }
                }
            }
        }
        if (visited.find(to) != visited.end()) {
            return distance[to];
        }
        return -1;
    }

    // return the shortest length from u to v (using all types Vehicles)
    // -1 equal to "there is no way"
    // const char &forBetween = 'a' is for viaExpress
    static int multiDijkstra(const Graph &graph, const shared_ptr<Station> &from, const shared_ptr<Station> &to, map<char, int> &a,bool consider = false) {
        checkVertex(graph, from);
        checkVertex(graph, to);

        //create map to store the distance between from to each vertex
        // {Bus = 'b', Rail = 'r', Tram = 't', Sprinter = 's', for the start('a'), z = null}
        map<shared_ptr<Station>, map<char, int>, comparator> distance;

        // set for the visited vertexes
        set<shared_ptr<Station>, comparator> visited = {from};

        // priorityQueue
        vector<shared_ptr<Station>> pqv = {from};


        // init infinity for the algorithm
        for (const auto &vertexPair: graph.vertexToIncidences) {
            shared_ptr<Station> vertex = vertexPair.first;
            distance[vertex]['b'] = numeric_limits<int>::max();
            distance[vertex]['r'] = numeric_limits<int>::max();
            distance[vertex]['t'] = numeric_limits<int>::max();
            distance[vertex]['s'] = numeric_limits<int>::max();
        }
        distance[from] = a;

        while (!pqv.empty()) {
            shared_ptr<Station> current = pqv[0];
            pqv.erase(pqv.begin());

            visited.insert(current);
            if (*current == *to) {
                a = distance[current];
                return getMin(distance[current]);
            }
            for (const auto &edge: graph.vertexToIncidences.at(current)) {
                shared_ptr<Station> neighbor = edge.v;
                if (visited.find(neighbor) != visited.end()) {
                    continue;
                }
                for (auto &toPair: distance[neighbor]) {
                    int weight = edge.label->getDistance() + distance[current][edge.label->getType()];
                    if (*neighbor == *to && !consider) {
                        // no need to add
                    } else if (edge.label->getType() == toPair.first) { // same Vehicle
                        weight += edge.label->getExchange();
                    } else {      // transit
                        weight += neighbor->getExchange();
                    }
                    if (weight < toPair.second) {
                        toPair.second = weight;
                    }
                }
                // check who's the minimums each types to the pq
                if (std::find(pqv.begin(), pqv.end(), neighbor) == pqv.end()) {
                    pqv.push_back(neighbor);
                }
                make_heap(pqv.begin(), pqv.end(), [&](const shared_ptr<Station> &a, const shared_ptr<Station> &b) {
                    return getMin(distance[a]) > getMin(distance[b]);
                });
            }
        }
        return -1;
    }

//     return the shortest length from u between z to v (using all types Vehicles)
//     -1 equal to "there is no way"
    static int viaDijkstra(const Graph &graph, const shared_ptr<Station> &from, const shared_ptr<Station> &to,const shared_ptr<Station> &between) {
        checkVertex(graph, from);
        checkVertex(graph, to);
        checkVertex(graph, between);

        map<char, int> typeBetween;
        typeBetween['b'] = 0;
        typeBetween['r'] = 0;
        typeBetween['s'] = 0;
        typeBetween['t'] = 0;
        int disFromBetween = multiDijkstra(graph, from, between, typeBetween, true);
        if (disFromBetween == -1) {      // if the is no way from to between
            return -1;
        }
        if (*between == *to) {
            return getMin(typeBetween);
        }

        int disBetweenTo = multiDijkstra(graph, between, to, typeBetween);
        if (disBetweenTo == -1) {
            return -1;
        }
        return disBetweenTo;
    }

    static int getMin(const map<char, int> &m) {
        int min = numeric_limits<int>::max();
        for (auto &tup: m) {
            if (tup.second < min) {
                min = tup.second;
            }
        }
        return min;
    }

//    // print every vertex with the edges from him with weight and type Vehicle
//    void printGraph()const{
//        for (const auto & vertex : vertexToIncidences){
//            cout << *vertex.first << " ";
//            vector<Edge> tmp = vertex.second;
//            vector<Edge>::iterator itEdge;
//            for (const auto &Edge : tmp){
//                cout << "[" << "from " << Edge.u->getName() << ", to " << Edge.v->getName() << " (by '" << Edge.label->getType() << "') = " << Edge.label->getDistance() << "] ";
//            }
//            cout << '\n';
//        }
//    }

//    static int getMax(const map<char,int> &m){
//        int x = 0;
//        for (auto &tup : m){
//            if (tup.second < numeric_limits<int>::max()){
//                if (tup.second > x){
//                    x = tup.second;
//                }
//            }
//        }
//        return x;
//    }

//    static bool containEdgeType(const map<char,int> &m, char c){
//        for (auto &tup : m){
//            if (tup.first == c){
//                if (tup.second < numeric_limits<int>::max()){
//                    return true;
//                }
//            }
//        }
//        return false;
//    }
};

#endif //EX_2_GRAPH_H