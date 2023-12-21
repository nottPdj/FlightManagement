#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <unordered_set>
#include "Airport.h"

using namespace std;




class Graph {
    std::unordered_set<Airport *, AirportHash, AirportEqual> airports;
    std::unordered_map<std::string, vector<Airport *>> airportsPerCity;
    std::unordered_set<Airport *, AirlineHash, AirlineEqual> airlines;

    void dfsVisit(Airport *v,  vector<T> & res) const;
    bool dfsIsDAG(Airport *v) const;
public:
    Airport *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addFlight(const T &sourc, const T &dest, double w);
    bool removeFlight(const T &sourc, const T &dest);
    vector<Airport * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    bool dfsDAG(const T &source);

    std::vector<Airport *> getAirports();
    std::vector<Flight> getFlights();
    std::vector<Airline *> getAirlines();
    std::vector<Flight> getFlightsFromAirport(std::string code);
    std::vector<Flight> getFlightsFromCity(std::string city);
    std::vector<Flight> getFlightsPerAirline(std::string airline);
    std::vector<Airport *> getReachableAirportsFrom(std::string code, int stops); // t
    std::vector<std::string> getReachableCitiesFrom(std::string code, int stops);
    std::vector<std::string> getReachableCountriesFrom(std::string code, int stops);
    std::vector<Flight> getMaxTrip(); // t
    std::vector<Airport *> getGreatestNumFlights();
    std::vector<Airport *> getEssentialAirports();
    std::vector<std::vector<Flight>> getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, vector<std::string> airlineCodes);
};


#endif //PROJETO2_GRAPH_H
