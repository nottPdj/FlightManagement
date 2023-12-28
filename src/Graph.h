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

/**
 * @brief Graph is the class that represents the graph which contains all the information about the flight system
 */

class Graph {
    /**
     * @brief Auxiliary struct for map hashing
     */
    struct CityCountryHash {
        std::size_t operator()(const std::pair<std::string, std::string>& p) const {
            std::size_t cityHash = std::hash<std::string>{}(p.first);
            std::size_t countryHash = std::hash<std::string>{}(p.second);
            return cityHash ^ (countryHash << 1);
        }
    };
     /**
     * @brief Auxiliary struct to compare the equality of a city
      * @note Different countries have cities with the same name
     */
    struct CityCountryEqual {
        bool operator()(const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };

    /**
     * @brief Auxiliary struct for ordering the cities in a set
     */
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
    std::vector<std::vector<Flight>> getMaxTrip(); // t
    std::vector<Airport *> getGreatestNumFlights(int top);
    std::vector<Airport *> getEssentialAirports();
    std::vector<std::vector<Flight>> getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, std::vector<std::string> airlineCodes);
     std::vector<Airport*> getNearestAirports(double latitude, double longitude);
};


#endif //PROJETO2_GRAPH_H
