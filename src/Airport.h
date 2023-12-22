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
    std::vector<Flight> flights;  // list of outgoing flights
    bool visited;          // auxiliary field
    bool processing;
    void addFlight(Flight flight);
    bool removeFlightTo(Airport *d);
public:
    Airport(std::string code,
    std::string name,
    std::string city,
    std::string country,
    std::string latitude,
    std::string longitude);
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    std::string getLatitude() const;
    std::string getLongitude() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Flight > &getAdj() const;
    void setAdj(const vector<Flight> &adj);
    friend class Graph;

    static bool byCode(Airport *a1, Airport *a2);
    static bool byName(Airport *a1, Airport *a2);
    static bool byCity(Airport *a1, Airport *a2);
    static bool byCountry(Airport *a1, Airport *a2);
    static bool byLatitude(Airport *a1, Airport *a2);
    static bool byLongitude(Airport *a1, Airport *a2);
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
