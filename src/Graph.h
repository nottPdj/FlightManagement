#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "Airport.h"


class Graph {
    std::vector<Airport*> vAirports;
    std::unordered_map<std::string, Airport *> airports;
    std::unordered_map<std::string, Airport *> airportsName;
    std::unordered_map<std::string, std::vector<Airport *>> airportsPerCity;
    std::unordered_map<std::string, Airline *> airlines;


    int calculateMaxDistanceFrom(Airport * source);
    std::vector<Flight> getMinTrip(Airport * source, Airport * dest);
    std::vector<Flight> getMinTripAirlines(Airport * source, Airport * dest, std::vector<std::string> use);
    bool lessThanMaxAirlines(std::vector<Flight> trip, int max);

public:
    void addFlight(Flight flight);

    std::vector<Airport*> getvAirports();
    Airport* getAirport(std::string code);
    std::vector<Airport*> getAirportByCity(std::string city);
    Airport* getAirportByName(std::string name);
    Airline* getAirline(std::string code);
    void addAirport(Airport* airport);
    void addAirline(Airline* airline);
    void resetVisited();

    int getNumAirports();
    int getNumFlights();
    int getNumAirlines();
    std::pair<int,int> getNumFlightsFromAirport(std::string code);
    int getNumFlightsFromCity(std::string city);
    int getNumFlightsPerAirline(std::string airline);
    std::vector<std::string> getCountriesFromCity(std::string city);
    std::vector<Airport *> getReachableAirportsFrom(std::string code, int stops); // t
    std::vector<std::string> getReachableCitiesFrom(std::string code, int stops);
    std::vector<std::string> getReachableCountriesFrom(std::string code, int stops);
    std::vector<std::vector<Flight>> getMaxTrip(); // t
    std::vector<Airport *> getGreatestNumFlights(int top);
    std::vector<Airport *> getEssentialAirports();
    std::vector<std::vector<Flight>> getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, std::vector<std::string> airlineCodes);
     std::vector<Airport*> getNearestAirports(double latitude, double longitude);
};


#endif //PROJETO2_GRAPH_H
