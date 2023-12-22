#include "Graph.h"

std::vector<Airport *> Graph::getvAirports() {
    return vAirports;
}

Airport *Graph::getAirport(std::string code) {
    return this->airports[code];
}

Airline *Graph::getAirline(std::string code) {
    return this->airlines[code];
}

void Graph::addFlight(Flight flight) {
    flight.source->addFlight(flight);
}

void Graph::addAirport(std::string code, Airport* airport) {
    vAirports.push_back(airport);
    airports.insert(make_pair(code, airport));
}

void Graph::addAirline(std::string code, Airline* airline) {
    airlines.insert(make_pair(code, airline));
}


int Graph::getNumAirports() {
    return airports.size();
}

int Graph::getNumFlights() {
    int n=0;
    for(auto ap:getvAirports()){
        n+=ap->getFlights().size();
    }
    return n;
}

int Graph::getNumAirlines() {
    return airlines.size();
}

std::pair<int,int> Graph::getNumFlightsFromAirport(std::string code) {
    std::pair<int,int> res;
    Airport * airport = getAirport(code);
    int nflights = airport->flights.size();
    std::set<std::string> nairlines;
    for(Flight f:airport->flights){
        nairlines.insert(f.getAirline()->getCode());
    }
    res={nflights,nairlines.size()};
    return res;
}

int Graph::getNumFlightsFromCity(std::string city) {
    int n=0;
    std::vector<Airport*> airportsInCity = airportsPerCity[city];
    for(Airport* ap:airportsInCity){
        n+=ap->getFlights().size();
    }
    return n;
}

//TODO
int Graph::getNumFlightsPerAirline(std::string airline) {
    return 0;
}

std::vector<std::string> Graph::printCountriesFromCity(std::string city) {
    return std::vector<std::string>();
}

std::vector<Airport *> Graph::getReachableAirportsFrom(std::string code, int stops) {
    return std::vector<Airport *>();
}

std::vector<std::string> Graph::getReachableCitiesFrom(std::string code, int stops) {
    return std::vector<std::string>();
}

std::vector<std::string> Graph::getReachableCountriesFrom(std::string code, int stops) {
    return std::vector<std::string>();
}

std::vector<Flight> Graph::getMaxTrip() {
    return std::vector<Flight>();
}

std::vector<Airport *> Graph::getGreatestNumFlights() {
    return std::vector<Airport *>();
}

std::vector<Airport *> Graph::getEssentialAirports() {
    return std::vector<Airport *>();
}

std::vector<std::vector<Flight>>
Graph::getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines,
                     std::vector<std::string> airlineCodes) {
    return std::vector<std::vector<Flight>>();
}






