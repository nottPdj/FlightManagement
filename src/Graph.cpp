#include "Graph.h"
#include <cmath>

std::vector<Airport *> Graph::getvAirports() {
    return vAirports;
}

Airport *Graph::getAirport(std::string code) {
    return this->airports[code];
}

std::vector<Airport*> Graph::getAirportByCity(std::string city) {
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
    auto cityIt=airportsPerCity.find(airport->getCity());
    if(cityIt!=airportsPerCity.end()){
        cityIt->second.push_back(airport);
    }
    else{
        airportsPerCity[airport->getCity()]={airport};
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
    //TODO verificar se airport existe senao crasha
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
        int size = aux.size();
        for (int i = 0; i < size; i++) {
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

std::vector<Airport *> Graph::getNearestAirports(double lat1, double lon1) {
    std::vector<Airport *> nearest;
    double maxDist = 0;

    for (Airport* a : vAirports){
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

        if (distance == maxDist){
            nearest.push_back(a);
        }
        else if (distance > maxDist){
            nearest.clear();
            nearest.push_back(a);
            maxDist = distance;
        }
    }
    return nearest;
}