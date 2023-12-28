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
    struct CityCountryHash {
        std::size_t operator()(const std::pair<std::string, std::string>& p) const {
            std::size_t cityHash = std::hash<std::string>{}(p.first);
            std::size_t countryHash = std::hash<std::string>{}(p.second);
            return cityHash ^ (countryHash << 1);
        }
    };

    struct CityCountryEqual {
        bool operator()(const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };

    struct CityCountryLess {
        bool operator()(const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) const {
            if (lhs.first == rhs.first) {
                return lhs.second < rhs.second;
            }
            return lhs.first < rhs.first;
        }
    };

    std::vector<Airport*> vAirports;
    std::unordered_map<std::string, Airport *> airports;
    std::unordered_map<std::string, Airport *> airportsName;
    std::unordered_map<std::pair<std::string, std::string>, std::vector<Airport *>, CityCountryHash, CityCountryEqual> airportsPerCity;
    std::unordered_map<std::string, Airline *> airlines;


    int calculateMaxDistanceFrom(Airport * source);
    std::vector<std::vector<Flight>> getMinTrips(Airport * source, Airport * dest);
    std::vector<std::vector<Flight>> getMinTripsAirlines(Airport * source, Airport * dest, std::vector<std::string> use);
    bool lessThanMaxAirlines(std::vector<Flight> trip, int max);

public:
    void addFlight(Flight flight);

    std::vector<Airport*> getvAirports();
    Airport* getAirport(std::string code);
    std::vector<Airport*> getAirportByCity(std::pair<std::string, std::string> city);
    Airport* getAirportByName(std::string name);
    Airline* getAirline(std::string code);
    void addAirport(Airport* airport);
    void addAirline(Airline* airline);
    void resetVisited();
    void resetProcessing();


    int getNumAirports();
    int getNumFlights();
    int getNumAirlines();
    std::pair<int,int> getNumFlightsFromAirport(std::string code);
    int getNumFlightsFromCity(std::pair<std::string, std::string> city);
    int getNumFlightsPerAirline(std::string airline);
    std::vector<std::string> getCountriesFromCity(std::pair<std::string, std::string> city);
    std::vector<Airport *> getReachableAirportsFrom(std::string code, int stops);
    std::vector<std::pair<std::string, std::string>> getReachableCitiesFrom(std::string code, int stops);
    std::vector<std::string> getReachableCountriesFrom(std::string code, int stops);
    std::vector<std::pair<Airport *, Airport *>> getMaxTrip(int &stops);
    std::vector<Airport *> getGreatestNumFlights(int top);
    std::vector<Airport *> getEssentialAirports();
    std::vector<std::vector<Flight>> getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, std::vector<std::string> airlineCodes);
     std::vector<Airport*> getNearestAirports(double latitude, double longitude);
};


#endif //PROJETO2_GRAPH_H
