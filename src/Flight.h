#ifndef PROJETO2_FLIGHT_H
#define PROJETO2_FLIGHT_H


#include <string>
#include "Airport.h"
#include "Airline.h"

class Flight {
    Airport * source;
    Airport * dest;      // destination vertex
    Airline * airline;
public:
    Flight(Airport *source, Airport *dest, Airline *airline);
    Airport *getSource() const;
    Airport *getDest() const;
    Airline *getAirline() const;
    void setDest(Airport *dest);



    static bool bySourceCode(Flight f1, Flight f2);
    static bool bySourceCity(Flight f1, Flight f2);
    static bool bySourceCountry(Flight f1, Flight f2);
    static bool byDestCode(Flight f1, Flight f2);
    static bool byDestCity(Flight f1, Flight f2);
    static bool byDestCountry(Flight f1, Flight f2);
    static bool byAirlineCode(Flight f1, Flight f2);

    friend class Graph;
    friend class Airport;

};


#endif //PROJETO2_FLIGHT_H
