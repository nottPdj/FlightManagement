#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "Airport.h"


class Graph {
    std::unordered_map<std::string, Airport *> airports;
    std::unordered_map<std::string, std::vector<Airport *>> airportsPerCity;
    std::unordered_map<std::string, Airline *> airlines;

    void dfsVisit(Airport *v,  vector<T> & res) const;
    bool dfsIsDAG(Airport *v) const;
public:
    int getNumVertex() const;
    void addFlight(Flight flight);
    vector<Airport * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    bool dfsDAG(const T &source);

    Airport* getAirport(std::string code);
    Airline* getAirline(std::string code);
    void addAirport(std::string code, Airport* airport);
    void addAirline(std::string code, Airline* airline);

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
