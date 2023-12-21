#ifndef PROJETO2_FLIGHT_H
#define PROJETO2_FLIGHT_H


#include <string>
#include "Airport.h"
#include "Airline.h"

class Flight {
    Airport * source;
    Airport * dest;      // destination vertex
    Airline * airline;
    double weight;         // edge weight
public:
    Flight(Airport *d, double w);
    Airport *getDest() const;
    void setDest(Airport *dest);
    Airline getAirline();
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph;
    friend class Airport;
};


#endif //PROJETO2_FLIGHT_H
