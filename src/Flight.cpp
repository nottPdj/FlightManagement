#include "Flight.h"

Flight::Flight(Airport* source, Airport* dest, Airline* airline) {
    this->source=source;
    this->dest=dest;
    this->airline=airline;
}

Airport *Flight::getSource() const {
    return source;
}

Airport *Flight::getDest() const {
    return dest;
}

Airline *Flight::getAirline() const {
    return airline;
}



bool Flight::bySourceCode(Flight f1, Flight f2) {
    return f1.getSource()->getCode() <= f2.getSource()->getCode();
}

bool Flight::bySourceCity(Flight f1, Flight f2) {
    return f1.getSource()->getCity() <= f2.getSource()->getCity();
}

bool Flight::bySourceCountry(Flight f1, Flight f2) {
    return f1.getSource()->getCountry() <= f2.getSource()->getCountry();
}

bool Flight::byDestCode(Flight f1, Flight f2) {
    return f1.getDest()->getCode() <= f2.getDest()->getCode();
}

bool Flight::byDestCity(Flight f1, Flight f2) {
    return f1.getDest()->getCity() <= f2.getDest()->getCity();
}

bool Flight::byDestCountry(Flight f1, Flight f2) {
    return f1.getDest()->getCountry() <= f2.getDest()->getCountry();
}

bool Flight::byAirlineCode(Flight f1, Flight f2) {
    return f1.getAirline()->getCode() <= f2.getAirline()->getCode();
}
