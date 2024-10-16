#include <sstream>
#include "Graph.h"
#include <cmath>
#include <iomanip>
#include <iostream>

/**
 * @brief Gets all the airports
 * @return vAirports
 */
std::vector<Airport *> Graph::getvAirports() {
    return vAirports;
}

/**
 * @brief Gets a airport using its code
 * @param code
 */
Airport *Graph::getAirport(std::string code) {
    return this->airports[code];
}

/**
 * @brief Gets the airports by the city where they are located
 * @param city
 */
std::vector<Airport*> Graph::getAirportByCity(std::pair<std::string, std::string> city) {
    return this->airportsPerCity[city];
}

/**
 * @brief Gets the airport by its name
 * @param name
 */
Airport *Graph::getAirportByName(std::string name) {
    return this->airportsName[name];
}

/**
 * @brief Gets a airline by its code
 * @param code
 * @return
 */
Airline *Graph::getAirline(std::string code) {
    return this->airlines[code];
}

/**
 * @brief Adds a flight (edge) to the graph
 * @param flight
 */
void Graph::addFlight(Flight flight) {
    flight.source->addFlight(flight);
}

/**
 * @brief Adds a airport (vertex) to the graph
 * @param airport
 */
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

/**
 * @brief Adds a airline to the graph
 * @param airline
 */
void Graph::addAirline(Airline* airline) {
    airlines.insert(make_pair(airline->getCode(), airline));
}

/**
 *@brief Gets the number of airports (vertices) of the graph
 */
int Graph::getNumAirports() {
    return airports.size();
}

/**
 * @brief Gets the number of flights (edges) of the graph
 * @details Time Complexity = O(V)
 */
int Graph::getNumFlights() {
    int n=0;
    for(auto ap:getvAirports()){
        n+=ap->getFlights().size();
    }
    return n;
}

/**
 * @brief Gets the number of airlines of the graph
 */
int Graph::getNumAirlines() {
    return airlines.size();
}

/**
 * @brief Gets the number of flights (edges) and different airlines from a airport (vertex)
 * @param code
 * @return res
 * @details Time Complexity = O(n*log(m)) -> n is the number of edges from the airport, m is the number of different airlines
 */
std::pair<int,int> Graph::getNumFlightsFromAirport(std::string code) {
    std::pair<int,int> res;
    Airport * airport = getAirport(code);
    int nflights = airport->flights.size();
    std::set<std::string> nairlines;
    for(Flight f:airport->getFlights()){
        nairlines.insert(f.getAirline()->getCode());
    }
    res={nflights,nairlines.size()};
    return res;
}

/**
 * @brief Gets the number of flights from a city
 * @param city
 * @return n
 * @details Time Complexity = O(n) -> n is the number of airports in the city
 */
int Graph::getNumFlightsFromCity(std::pair<std::string, std::string> city) {
    int n=0;
    std::vector<Airport*> airportsInCity = airportsPerCity[city];
    for(Airport* ap:airportsInCity){
        n+=ap->getFlights().size();
    }
    return n;
}

/**
 * @brief Gets the number of flights per airline
 * @param airline
 * @return n
 * @details Time Complexity = O(V+E)
 */
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

/**
 * @brief Gets the countries that a given city flies to
 * @param city Source city
 * @return Countries that city flies to
 * @details Time Complexity = O(A*F*log(n)) ->A is the number of airports in the city,F is the number of flights per A,n is the number of countries in the set(countries)
 */
std::vector<std::string> Graph::getCountriesFromCity(std::pair<std::string, std::string> city) {
    std::set<std::string> countries;
    std::vector<Airport*> airportsInCity = airportsPerCity[city];
    for(auto ap:airportsInCity){
        for(auto f:ap->getFlights()){
                countries.insert(f.getDest()->getCountry());
        }
    }
    std::vector<std::string> res;
    for(std::string s:countries){res.push_back(s);}

    return res;
}

/**
 * @brief Gets the reachable airports from a given airport in a max number of stops
 * @param code Code from source airport
 * @param stops Max number of stops
 * @return Reachable airports from source in a max number of stops
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
std::vector<Airport *> Graph::getReachableAirportsFrom(std::string code, int stops) {
    std::vector<Airport *> res;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (!aux.empty()) {
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
    res.erase(res.begin());
    return res;
}

/**
 * @brief Gets the reachable cities from a given airport in a max number of stops
 * @param code Code from source airport
 * @param stops Max number of stops
 * @return Reachable cities from source in a max number of stops
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
std::vector<std::pair<std::string, std::string>> Graph::getReachableCitiesFrom(std::string code, int stops) {
    std::vector<std::pair<std::string, std::string>> res;
    std::set<std::pair<std::string, std::string>, CityCountryLess> cities;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (!aux.empty()) {
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            if (xStops != -1)
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

/**
 * @brief Gets the reachable countries from a given airport in a max number of stops
 * @param code Code from source airport
 * @param stops Max number of stops
 * @return Reachable countries from source in a max number of stops
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
std::vector<std::string> Graph::getReachableCountriesFrom(std::string code, int stops) {
    std::vector<std::string> res;
    std::set<std::string> countries;
    resetVisited();
    std::queue<Airport *> aux;
    Airport * airport = getAirport(code);
    aux.push(airport);
    airport->setVisited(true);
    int xStops = -1;
    while (!aux.empty()) {
        int size = aux.size();
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            if (xStops != -1)
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

/**
 * @brief Calculates the trip with the maximum distance starting from source and stores that distance and the destinations in the source
 * @param source Source
 * @return Distance of the maximum trip starting from source
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
int Graph::calculateMaxDistanceFrom(Airport * source) {
    resetVisited();
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
        if (aux.empty()) {
            source->setMaxTripDistance(distance);
            for (auto it = maxDests.begin(); it != maxDests.end(); it++) {
                source->addMaxTripDest(*it);
            }
            break;
        } else {
            distance++;
        }
    }
    return distance;
}

/**
 * @brief Gets the minimum trip (or trips, if equivalent) from source to dest
 * @param source Source
 * @param dest Destination
 * @return Vector with the minimum trips (vector of flights)
 * @details Time Complexity = O(V+E+F), V = nº airports, E = nº flights, F = total number of flights from the minimum trip(s)
 */
std::vector<std::vector<Flight>> Graph::getMinTrips(Airport * source, Airport * dest) {
    resetVisited();
    resetProcessing();
    std::vector<std::vector<Flight>> trips;
    std::unordered_map<Airport *, std::vector<Flight>> flightTo;
    std::queue<Airport *> aux;
    std::vector<Airport *> processing;
    bool foundDest = false;
    Airport * last;
    aux.push(source);
    source->setVisited(true);
    int distance = 0;
    while (!aux.empty()) {
        int size = aux.size();
        distance++;
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            for (Flight f: a->getFlights()) {
                if (!f.getDest()->isVisited()) {
                    if (!f.getDest()->isProcessing()) {
                        aux.push(f.getDest());
                        f.getDest()->setProcessing(true);
                        processing.push_back(f.getDest());
                    }
                    flightTo[f.getDest()].push_back(f);
                    if (f.getDest() == dest) {
                        last = dest;
                        foundDest = true;
                    }
                }
            }
        }
        if (foundDest) {
            std::queue<std::deque<Flight>> tripsReversed;
            std::vector<Flight> flightsToLast = flightTo.find(last)->second;
            for (Flight f : flightsToLast) {
                std::deque<Flight> tripReversed;
                tripReversed.push_front(f);
                tripsReversed.push(tripReversed);
            }
            bool end = false;
            while (true) {
                int size = tripsReversed.size();
                for (int i = 0; i < size; i++) {
                    auto tripR = tripsReversed.front();
                    tripsReversed.pop();
                    last = tripR.front().getSource();

                    if (last == source) {
                        end = true;
                        std::vector<Flight> trip;
                        while (!tripR.empty()) {
                            trip.push_back(tripR.front());
                            tripR.pop_front();
                        }
                        trips.push_back(trip);
                    } else {
                        flightsToLast = flightTo.find(last)->second;
                        for (Flight f: flightsToLast) {
                            std::deque<Flight> tripReversed = tripR;
                            tripReversed.push_front(f);
                            tripsReversed.push(tripReversed);
                        }
                    }
                }
                if (end) {
                    return trips;
                }
            }
        }

        for (Airport * a : processing) {
            a->setProcessing(false);
            a->setVisited(true);
        }
    }
    return trips;
}

/**
 * @brief Gets the minimum trip (or trips, if equivalent) from source to dest only using specified airlines
 * @param source Source
 * @param dest Destination
 * @param use Airlines that can be used
 * @return Vector with the minimum trips (vector of flights)
 * @details Time Complexity = O(V+E+F), V = nº airports, E = nº flights, F = total number of flights from the minimum trip(s)
 */
std::vector<std::vector<Flight>> Graph::getMinTripsAirlines(Airport * source, Airport * dest, std::vector<std::string> use) {
    resetVisited();
    resetProcessing();
    std::vector<std::vector<Flight>> trips;
    std::unordered_map<Airport *, std::vector<Flight>> flightTo;
    std::queue<Airport *> aux;
    std::vector<Airport *> processing;
    bool foundDest = false;
    Airport * last;
    aux.push(source);
    source->setVisited(true);
    int distance = 0;
    while (!aux.empty()) {
        int size = aux.size();
        distance++;
        for (int i = 0; i < size; i++) {
            auto a = aux.front();
            aux.pop();
            for (Flight f: a->getFlights()) {
                if (!f.getDest()->isVisited() && (std::find(use.begin(), use.end(), f.getAirline()->getCode()) != use.end())) {
                    if (!f.getDest()->isProcessing()) {
                        aux.push(f.getDest());
                        f.getDest()->setProcessing(true);
                        processing.push_back(f.getDest());
                    }
                    flightTo[f.getDest()].push_back(f);
                    if (f.getDest() == dest) {
                        last = dest;
                        foundDest = true;
                    }
                }
            }
        }
        if (foundDest) {
            std::queue<std::deque<Flight>> tripsReversed;
            std::vector<Flight> flightsToLast = flightTo.find(last)->second;
            for (Flight f : flightsToLast) {
                std::deque<Flight> tripReversed;
                tripReversed.push_front(f);
                tripsReversed.push(tripReversed);
            }
            bool end = false;
            while (true) {
                int size = tripsReversed.size();
                for (int i = 0; i < size; i++) {
                    auto tripR = tripsReversed.front();
                    tripsReversed.pop();
                    last = tripR.front().getSource();

                    if (last == source) {
                        end = true;
                        std::vector<Flight> trip;
                        while (!tripR.empty()) {
                            trip.push_back(tripR.front());
                            tripR.pop_front();
                        }
                        trips.push_back(trip);
                    } else {
                        flightsToLast = flightTo.find(last)->second;
                        for (Flight f: flightsToLast) {
                            std::deque<Flight> tripReversed = tripR;
                            tripReversed.push_front(f);
                            tripsReversed.push(tripReversed);
                        }
                    }
                }
                if (end) {
                    return trips;
                }
            }
        }

        for (Airport * a : processing) {
            a->setProcessing(false);
            a->setVisited(true);
        }
    }
    return trips;
}

/**
 * @brief Gets the pair of source-destination airports (or pairs, if more than
one) that correspond to the maximum trip, that is, the flight trip(s) with the greatest number of stops in between them
 * @param stops Stops of the maximum trip
 * @return Vector with the pairs of source-destination airports
 * @details Time Complexity = O(V(V+E)), V = nº airports, E = nº flights
 */
std::vector<std::pair<Airport *, Airport *>> Graph::getMaxTrip(int &stops) {
    std::set<std::pair<Airport *, Airport *>> maxTrips;
    std::vector<std::pair<Airport *, Airport *>> sourceDests;
    int maxDistance = 0;
    for (Airport * a : getvAirports()) {
        maxDistance = std::max(maxDistance, calculateMaxDistanceFrom(a));
    }
    for (Airport * a : getvAirports()) {
        if (a->getMaxTripDistance() == maxDistance) {
            for (Airport * dest : a->getMaxTripDests()) {
                maxTrips.insert(std::make_pair(a, dest));
            }
        }
    }
    for (auto sourceDest : maxTrips) {
        sourceDests.push_back(sourceDest);
    }
    stops = maxDistance - 1;
    return sourceDests;
}

/**
 * @brief Gets a vector with a given size of the airports with the most flight out
 * @param n Number of airports to show
 * @return vector with size n containing the airports with the most flights out
 * @details Time Complexity = O(V), V = nº airports
 */
std::vector<Airport *> Graph::getGreatestNumFlights(int n) {

    struct compareNFlightsOut {
        bool operator()(Airport* a, Airport* b) {
            return a->getNFlightsOut() > b->getNFlightsOut();
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

/**
 * @brief Auxiliary function to check if a stack contains a certain string
 * @param i
 * @param s
 * @details Time complexity O(n) -> n is the size of the stack
 */
bool contains(std::string i ,std::stack<std::string>s){
    while(!s.empty()){
        if(s.top()==i){
            return true;
        }
        s.pop();
    }
    return false;
}

/**
 * @brief Auxiliary Deep-First-Search function to get essential airports
 * @param airport
 * @param s
 * @param l
 * @param i
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
void dfs_essential(Airport* airport, std::stack<std::string> &s, std::unordered_set<Airport*> &l, int &i, Airport * parent=nullptr) {
    airport->setLow(i);
    airport->setNum(i);
    i++;
    s.push(airport->getCode());
    int children =0;
    for (Flight f: airport->getFlights()) {
        if (f.getDest()->getNum() == 0) {
            dfs_essential(f.getDest(), s, l, i,airport);
            airport->setLow(std::min(airport->getLow(), f.getDest()->getLow()));

            if ( f.getDest()->getLow() >=airport->getNum())
                l.insert(airport);
            children++;
        } else if (contains(f.getDest()->getCode(), s)) {
            airport->setLow(std::min(airport->getLow(), f.getDest()->getNum()));
        }
    }
    if (parent == nullptr && children >= 2)
        l.insert(airport);
    s.pop();
}

/**
 * @brief Gets the airports that are essential to the network's
 * @return v
 * @details Time Complexity = O(V+E), V = nº airports, E = nº flights
 */
std::vector<Airport *> Graph::getEssentialAirports() {
    std::vector<Airport*> v;
    std::unordered_set<Airport*> l;
    std::stack<std::string> s;
    int i = 1;

    for (Airport* ap : getvAirports()) {
        ap->setNum(0);
    }
    Airline toDelete = Airline("x","x","x","x");
    for (Airport* ap : getvAirports()) {
        for (auto f : ap->getFlights()) {
            if(f.getAirline()->getCode()!="x")
                 f.getDest()->addFlight(Flight(f.getDest(), f.getSource(), &toDelete));
        }
    }
    for (Airport* ap : getvAirports()) {
        ap->setNum(0);
    }

    for (Airport* ap : getvAirports()) {
        if (ap->getNum() == 0) {
            dfs_essential(ap, s, l, i);
        }
    }
    for (Airport* ap : vAirports) {
        ap->deleteFlightsByAirline("x");
    }

    v.assign(l.begin(), l.end());

    return v;
}

/**
 * @brief Verifies if it are used fewer than max airlines in a set of flights
 * @param trip Flights
 * @param max Maximum number of airlines that can be used
 * @return True if it aren't used more airlines than max, false otherwise
 */
bool Graph::lessThanMaxAirlines(std::vector<Flight> trip, int max) {
    int n = 0;
    std::set<Airline *> used;
    for (Flight f : trip) {
        if (used.find(f.getAirline()) == used.end()) {
            used.insert(f.getAirline());
        }
        if (used.size() > max) {
            return false;
        }
    }
    return true;
}

/**
 *  @brief Gets the best flight option (or the set of options if they are equivalent), for a given source and
destination location.
 If specified by client the best flight option(s) have the constraint of a maximum number of airlines used.
 If specified by client the best flight option(s) have the constraint of using only specified airlines.
 * @param source Source location
 * @param searchFrom Type of source
 * @param dest Destination location
 * @param searchTo Type of dest
 * @param maxAirlines Maximum number of airlines that can be used
 * @param airlineCodes Codes of the only airlines that can be used
 * @return Vector with the best options
 * @details Time Complexity = O(S*D*(V+E+F)), S = nº airports in (or closest) source location, D = nº airports in (or closest) destination location,
 * V = nº airports, E = nº flights, F = total number of flights from the minimum trip(s)
 */
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
            std::istringstream iss(dest);
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
            std::istringstream iss(dest);
            iss >> latitude;
            iss >> std::setw(1) >> nothing >> longitude;
            std::vector<Airport *> nearestAirports = getNearestAirports(latitude, longitude);
            for (Airport *a: nearestAirports) {
                to.push_back(a);
            }
            break;
        }
    }

    std::vector<std::vector<Flight>> trips;
    for (Airport * aSource : from) {
        for (Airport * aDest : to) {
            if (airlineCodes.empty()) {
                for (auto trip : getMinTrips(aSource, aDest)) {
                    trips.push_back(trip);
                }
            } else {
                for (auto trip : getMinTripsAirlines(aSource, aDest, airlineCodes)) {
                    trips.push_back(trip);
                }
            }
            if (maxAirlines != -1) {
                for (auto trip: trips) {
                    if (lessThanMaxAirlines(trip, maxAirlines)) {
                        bestOptions.push_back(trip);
                    }
                }
                return bestOptions;
            } else {
                for (auto trip: trips) {
                    bestOptions.push_back(trip);
                }
            }
        }
    }

    return bestOptions;
}

/**
 * @brief Sets visited to false for all the airports
 * @details Time Complexity = O(V),  V = nº airports
 */
void Graph::resetVisited() {
    for (auto airport : getvAirports()) {
        airport->setVisited(false);
    }
}

/**
 * @brief Sets processing to false for all the airports
 * @details Time Complexity = O(V),  V = nº airports
 */
void Graph::resetProcessing() {
    for (auto airport : getvAirports()) {
        airport->setProcessing(false);
    }
}

/**
 * @brief Gets the closest airport (or more, if at the same distance) to the coordinates given
 * @param lat Given latitude
 * @param lon Given longitude
 * @return Vector with the airports closer to the point given (usually with size 1)
 * @details Time Complexity = O(V), V = nº airports
 */
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