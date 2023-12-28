#include <sstream>
#include "Graph.h"
#include <cmath>
#include <iomanip>
#include <iostream>

std::vector<Airport *> Graph::getvAirports() {
    return vAirports;
}

Airport *Graph::getAirport(std::string code) {
    return this->airports[code];
}

std::vector<Airport*> Graph::getAirportByCity(std::pair<std::string, std::string> city) {
    return this->airportsPerCity[city];
}

Airport *Graph::getAirportByName(std::string name) {
    return this->airportsName[name];
}

Airline *Graph::getAirline(std::string code) {
    return this->airlines[code];
}

void Graph::addFlight(Flight flight) {
    flight.source->addFlight(flight);
}

void Graph::addAirport(Airport* airport) {
    vAirports.push_back(airport);
    airports.insert(make_pair(airport->getCode(), airport));
    airportsName.insert(make_pair(airport->getName(), airport));
    auto cityIt=airportsPerCity.find(make_pair(airport->getCity(), airport->getCountry()));
    if(cityIt!=airportsPerCity.end()){
        cityIt->second.push_back(airport);
    }
    else{
        airportsPerCity[make_pair(airport->getCity(), airport->getCountry())]={airport};
    }
}

void Graph::addAirline(Airline* airline) {
    airlines.insert(make_pair(airline->getCode(), airline));
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

int Graph::getNumFlightsFromCity(std::pair<std::string, std::string> city) {
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

std::vector<std::string> Graph::getCountriesFromCity(std::pair<std::string, std::string> city) {
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
        int size = aux.size();
        for (int i = 0; i < size; i++) {
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

std::vector<std::pair<std::string, std::string>> Graph::getReachableCitiesFrom(std::string code, int stops) {
    std::vector<std::pair<std::string, std::string>> res;
    std::set<std::pair<std::string, std::string>, CityCountryLess> cities;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (true) {
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            cities.insert(make_pair(a->getCity(), a->getCountry()));
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
                cities.insert(make_pair(aux.front()->getCity(), aux.front()->getCountry()));
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
        int size = aux.size();
        for (int i = 0; i < size; i++) {
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



int Graph::calculateMaxDistanceFrom(Airport * source) {
    resetVisited();
    if (source->getCode() == "STZ") {
        int x = 0;
    }
    std::queue<Airport *> aux;
    aux.push(source);
    source->setVisited(true);
    int distance = 0;
    while (!aux.empty()) {
        std::unordered_set<Airport *> maxDests;
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            bool end = true;
            for (auto f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    end = false;
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                }
            }
            if (end) {
                maxDests.insert(a);
            }
        }
        distance++;
        if (aux.empty()) {
            source->setMaxTripDistance(distance);
            for (auto it = maxDests.begin(); it != maxDests.end(); it++) {
                source->addMaxTripDest(*it);
            }
            break;
        }
    }
    return distance;
}

// encontrar caminho mais rapido (menos paragens) entre source e dest
std::vector<Flight> Graph::getMinTrip(Airport * source, Airport * dest) {
    resetVisited();
    std::deque<Flight> tripReversed;
    std::vector<Flight> trip;
    std::unordered_map<Airport *, Flight> flightTo;
    std::queue<Airport *> aux;
    aux.push(source);
    source->setVisited(true);
    while (!aux.empty()) {
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            for (Flight f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                    flightTo.emplace(f.getDest(), f);
                    if (f.getDest() == dest) {
                        Airport *last = dest;
                        Flight flightToLast = flightTo.find(last)->second;
                        while (true) {
                            tripReversed.push_front(flightToLast);
                            last = flightToLast.getSource();
                            if (last == source) {
                                while (!tripReversed.empty()) {
                                    trip.push_back(tripReversed.front());
                                    tripReversed.pop_front();
                                }
                                return trip;
                            }
                            flightToLast = flightTo.find(last)->second;
                        }
                    }
                }
            }
        }
    }
    return trip;
}

// encontrar caminho mais rapido (menos paragens) entre source e dest with specific airlines
std::vector<Flight> Graph::getMinTripAirlines(Airport * source, Airport * dest, std::vector<std::string> use) {
    resetVisited();
    std::deque<Flight> tripReversed;
    std::vector<Flight> trip;
    std::unordered_map<Airport *, Flight> flightTo;
    std::queue<Airport *> aux;
    aux.push(source);
    source->setVisited(true);
    while (!aux.empty()) {
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            for (Flight f: a->getFlights()) {
                if (!f.getDest()->isVisited() && (std::find(use.begin(), use.end(), f.getAirline()->getCode()) != use.end())) {
                    aux.push(f.getDest());
                    f.getDest()->setVisited(true);
                    flightTo.emplace(f.getDest(), f);
                    if (f.getDest() == dest) {
                        Airport *last = dest;
                        Flight flightToLast = flightTo.find(last)->second;
                        while (true) {
                            tripReversed.push_front(flightToLast);
                            last = flightToLast.getSource();
                            if (last == source) {
                                while (!tripReversed.empty()) {
                                    trip.push_back(tripReversed.front());
                                    tripReversed.pop_front();
                                }
                                return trip;
                            }
                            flightToLast = flightTo.find(last)->second;
                        }
                    }
                }
            }
        }
    }
    return trip;
}

std::vector<std::vector<Flight>> Graph::getMaxTrip() {
    std::vector<std::vector<Flight>> maxTrips;
    int maxDistance = 0;
    for (Airport * a : getvAirports()) {
        maxDistance = std::max(maxDistance, calculateMaxDistanceFrom(a));
    }
    for (Airport * a : getvAirports()) {
        if (a->getMaxTripDistance() == maxDistance) {
            for (Airport * dest : a->getMaxTripDests()) {
                maxTrips.push_back(getMinTrip(a, dest));
            }
        }
    }
    return maxTrips;
}


std::vector<Airport *> Graph::getGreatestNumFlights(int n) {

    struct compareNFlightsOut {
        bool operator()(Airport* a, Airport* b) {
            return a->getNFlightsOut() > b->getNFlightsOut(); // This creates a max heap
        }
    };
    std::vector<Airport *> topFlights;
    std::priority_queue<Airport *, std::vector<Airport *>, compareNFlightsOut> topMin;

    for (Airport* a : getvAirports()){
        if (topMin.size() < n){
            topMin.push(a);
        }
        else {
            if (a->getNFlightsOut() > topMin.top()->getNFlightsOut()){
                topMin.pop();
                topMin.push(a);
            }
        }
    }
    while (!topMin.empty()) {
        topFlights.push_back(topMin.top());
        topMin.pop();
    }

    return topFlights;
}


bool contains(std::string i ,std::stack<std::string>s){
    while(!s.empty()){
        if(s.top()==i){
            return true;
        }
        s.pop();
    }
    return false;
}

void dfs_essential(Airport* airport, std::stack<std::string> &s, std::unordered_set<Airport*> &l, int &i) {
    airport->setLow(i);
    airport->setNum(i);
    i++;
    s.push(airport->getCode());

    for (Flight f: airport->getFlights()) {
        if (f.getDest()->getNum() == 0) {
            dfs_essential(f.getDest(), s, l, i);
            airport->setLow(std::min(airport->getLow(), f.getDest()->getLow()));

            if ( f.getDest()->getLow() >=airport->getNum())
                l.insert(airport);
        } else if (contains(f.getDest()->getCode(), s)) {
            airport->setLow(std::min(airport->getLow(), f.getDest()->getNum()));
        }
    }
    s.pop();
}

std::vector<Airport *> Graph::getEssentialAirports() {
    std::vector<Airport*> v;
    std::unordered_set<Airport*>l;
    std::stack<std::string>s;
    int i=1;
    for (Airport* ap : getvAirports()) {
        ap->setNum(0);
    }
    
    for(Airport * ap:getvAirports()){
        if(ap->getNum()==0){
            dfs_essential(ap,s,l,i);
        }
    }
    for(auto ap:l){
        v.push_back(ap);
    }
    return v;
}


bool Graph::lessThanMaxAirlines(std::vector<Flight> trip, int max) {
    int n = 0;
    std::vector<Airline *> used;
    for (Flight f : trip) {
        if (find(used.begin(), used.end(), f.getAirline()) == used.end()) {
            n++;
        }
        if (n > max) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<Flight>>
Graph::getBestOption(std::string source, int searchFrom, std::string dest, int searchTo, int maxAirlines, std::vector<std::string> airlineCodes) {
    std::vector<std::vector<Flight>> bestOptions;
    std::vector<Airport *> from;
    std::vector<Airport *> to;

    switch (searchFrom) {
        // Airport code
        case 0:
            from.push_back(getAirport(source));
            break;
        // Airport name
        case 1:
            from.push_back(getAirportByName(source));
            break;
        // City
        case 2: {
            std::string city;
            std::string country;
            std::string nothing;
            std::istringstream iss(source);
            std::getline(iss, city, ',');
            std::getline(iss, country);
            std::vector<Airport *> airportByCity = getAirportByCity(make_pair(city, country));
            for (Airport *a: airportByCity) {
                from.push_back(a);
            }
            break;
        }
        // Geographical coordinates (lat, lon)
        case 3: {
            double latitude;
            double longitude;
            std::string nothing;
            std::istringstream iss(source);
            iss >> latitude;
            iss >> std::setw(1) >> nothing >> longitude;
            std::vector<Airport *> nearestAirports = getNearestAirports(latitude, longitude);
            for (Airport *a: nearestAirports) {
                from.push_back(a);
            }
            break;
        }
    }

    switch (searchTo) {
        // Airport code
        case 0:
            to.push_back(getAirport(dest));
            break;
        // Airport name
        case 1:
            to.push_back(getAirportByName(dest));
            break;
        // City
        case 2: {
            std::string city;
            std::string country;
            std::string nothing;
            std::istringstream iss(source);
            std::getline(iss, city, ',');
            std::getline(iss, country);
            std::vector<Airport *> airportByCity = getAirportByCity(make_pair(city, country));
            for (Airport *a: airportByCity) {
                to.push_back(a);
            }
            break;
        }
        // Geographical coordinates (lat, lon)
        case 3: {
            double latitude;
            double longitude;
            std::string nothing;
            std::istringstream iss(source);
            iss >> latitude;
            iss >> std::setw(1) >> nothing >> longitude;
            std::vector<Airport *> nearestAirports = getNearestAirports(latitude, longitude);
            for (Airport *a: nearestAirports) {
                to.push_back(a);
            }
            break;
        }
    }

    for (Airport * aSource : from) {
        for (Airport * aDest : to) {
            std::vector<Flight> trip;
            if (airlineCodes.empty()) {
                trip = getMinTrip(aSource, aDest);
            } else {
                trip = getMinTripAirlines(aSource, aDest, airlineCodes);
            }
            if (lessThanMaxAirlines(trip, maxAirlines)) {
                bestOptions.push_back(trip);
            }
        }
    }

    return bestOptions;
}



void Graph::resetVisited() {
    for (auto airport : getvAirports()) {
        airport->setVisited(false);
    }
}

std::vector<Airport *> Graph::getNearestAirports(double lat, double lon) {
    std::vector<Airport *> nearest;
    double minDist = 6371;

    for (Airport* a : vAirports){
        double lat1 = lat;
        double lon1 = lon;
        double lat2 = stod(a->getLatitude());
        double lon2 = stod(a->getLongitude());
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;
        double aux = pow(sin(dLat / 2), 2) +
                   pow(sin(dLon / 2), 2) *
                   cos(lat1) * cos(lat2);

        double distance = 6371 * 2 * asin(sqrt(aux));

        if (distance == minDist){
            nearest.push_back(a);
        }
        else if (distance < minDist){
            nearest.clear();
            nearest.push_back(a);
            minDist = distance;
        }
    }
    return nearest;
}