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
    auto cityIt=airportsPerCity.find(airport->getCity());
    if(cityIt!=airportsPerCity.end()){
        cityIt->second.push_back(airport);
    }
    else{
        airportsPerCity[airport->getCity()]={airport};
    }
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

int Graph::getNumFlightsPerAirline(std::string airline) {
    int n=0;
    for(auto ap:vAirports){
        for(auto f: ap->getFlights()){
            if(f.getAirline()->getCode()==airline)
                n++;
        }
    }
    return n;
}

std::vector<std::string> Graph::getCountriesFromCity(std::string city) {
    std::vector<std::string> countries;
    std::vector<Airport*> airportsInCity = airportsPerCity[city];
    for(auto ap:airportsInCity){
        for(auto f:ap->getFlights()){
            if(std::find(countries.begin(),countries.end(),f.getDest()->getCountry())==countries.end())
                countries.push_back(f.getDest()->getCountry());
        }
    }
    return countries;
}

std::vector<Airport *> Graph::getReachableAirportsFrom(std::string code, int stops) {
    std::vector<Airport *> res;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (true) {
        for (int i = 0; i < aux.size(); i++) {
            auto a = aux.front();
            aux.pop();
            res.push_back(a);
            for (auto f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                }
            }
        }
        xStops++;
        if (xStops == stops) {
            while (!aux.empty()) {
                res.push_back(aux.front());
                aux.pop();
            }
            break;
        }
    }
    return res;
}

std::vector<std::string> Graph::getReachableCitiesFrom(std::string code, int stops) {
    std::vector<std::string> res;
    std::set<std::string> cities;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (true) {
        for (int i = 0; i < aux.size(); i++) {
            auto a = aux.front();
            aux.pop();
            cities.insert(a->getCity());
            for (auto f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                }
            }
        }
        xStops++;
        if (xStops == stops) {
            while (!aux.empty()) {
                cities.insert(aux.front()->getCity());
                aux.pop();
            }
            break;
        }
    }
    for (auto city : cities) {
        res.push_back(city);
    }
    return res;
}

std::vector<std::string> Graph::getReachableCountriesFrom(std::string code, int stops) {
    std::vector<std::string> res;
    std::set<std::string> countries;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (true) {
        for (int i = 0; i < aux.size(); i++) {
            auto a = aux.front();
            aux.pop();
            countries.insert(a->getCountry());
            for (auto f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                }
            }
        }
        xStops++;
        if (xStops == stops) {
            while (!aux.empty()) {
                countries.insert(aux.front()->getCountry());
                aux.pop();
            }
            break;
        }
    }
    for (auto country : countries) {
        res.push_back(country);
    }
    return res;
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

void Graph::resetVisited() {
    for (auto airport : getvAirports()) {
        airport->setVisited(false);
    }
}






