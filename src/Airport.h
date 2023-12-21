#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include <vector>
#include "Flight.h"

class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    std::string latitude;
    std::string longitude;
    std::vector<Flight> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;
    void addFlight(Airport *dest, double w);
    bool removeFlightTo(Airport *d);
public:
    Airport();
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Flight > &getAdj() const;
    void setAdj(const vector<Flight> &adj);
    friend class Graph;
};

// Hash function for the Airport class
struct AirportHash {
    std::size_t operator()(const Airport *airport) const {
        return std::hash<std::string>{}(airport->getCode());
    }
};

// Equality function for the Airport class
struct AirportEqual {
    bool operator()(const Airport *lhs, const Airport *rhs) const {
        return lhs->getCode() == rhs->getCode();
    }
};


#endif //PROJETO2_AIRPORT_H
