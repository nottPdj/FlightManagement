#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "Airport.h"


class Graph {
    std::vector<Airport*> vAirports;
    std::unordered_map<std::string, Airport *> airports;
    std::unordered_map<std::string, std::vector<Airport *>> airportsPerCity;
    std::unordered_map<std::string, Airline *> airlines;

public:
    void addFlight(Flight flight);

    std::vector<Airport*> getvAirports();
    Airport* getAirport(std::string code);
    Airline* getAirline(std::string code);
    void addAirport(std::string code, Airport* airport);
    void addAirline(std::string code, Airline* airline);

    int getNumAirports();
    int getNumFlights();
    int getNumAirlines();
    std::pair<int,int> getNumFlightsFromAirport(std::string code);
    int getNumFlightsFromCity(std::string city);
    int getNumFlightsPerAirline(std::string airline);
    std::vector<std::string> printCountriesFromCity(std::string city);
    std::vector<Airport *> getReachableAirportsFrom(std::string code, int stops); // t
    std::vector<std::string> getReachableCitiesFrom(std::string code, int stops);
    std::vector<std::string> getReachableCountriesFrom(std::string code, int stops);
    std::vector<Flight> getMaxTrip(); // t
    std::vector<Airport *> getGreatestNumFlights();
    std::vector<Airport *> getEssentialAirports();
    std::vector<std::vector<Flight>> getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, std::vector<std::string> airlineCodes);
};


#endif //PROJETO2_GRAPH_H
