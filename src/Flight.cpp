#include "Flight.h"

/**
 * @brief Constructor of Flight
 * @param source
 * @param dest
 * @param airline
 */
Flight::Flight(Airport* source, Airport* dest, Airline* airline) {
    this->source=source;
    this->dest=dest;
    this->airline=airline;
}

/**
 * @brief Gets the source airport of the flight
 * @return source
 */
Airport *Flight::getSource() const {
    return source;
}

/**
 * @brief Gets the destination airport of the flight
 * @return dest
 */
Airport *Flight::getDest() const {
    return dest;
}

/**
 * @brief Gets the airline of the flight
 * @return airline
 */
Airline *Flight::getAirline() const {
    return airline;
}


/**
 * @brief Boolean function to order flights by source airport code
 * @param f1
 * @param f2
 */
bool Flight::bySourceCode(Flight f1, Flight f2) {
    return f1.getSource()->getCode() <= f2.getSource()->getCode();
}

/**
 * @brief Boolean function to order flights by source airport city
 * @param f1
 * @param f2
 */
bool Flight::bySourceCity(Flight f1, Flight f2) {
    return f1.getSource()->getCity() <= f2.getSource()->getCity();
}

/**
 * @brief Boolean function to order flights by source airport country
 * @param f1
 * @param f2
 */
bool Flight::bySourceCountry(Flight f1, Flight f2) {
    return f1.getSource()->getCountry() <= f2.getSource()->getCountry();
}

/**
 * @brief Boolean function to order flights by destination airport code
 * @param f1
 * @param f2
 */
bool Flight::byDestCode(Flight f1, Flight f2) {
    return f1.getDest()->getCode() <= f2.getDest()->getCode();
}

/**
 * @brief Boolean function to order flights by destination airport city
 * @param f1
 * @param f2
 */
bool Flight::byDestCity(Flight f1, Flight f2) {
    return f1.getDest()->getCity() <= f2.getDest()->getCity();
}

/**
 * @brief Boolean function to order flights by destination airport country
 * @param f1
 * @param f2
 */
bool Flight::byDestCountry(Flight f1, Flight f2) {
    return f1.getDest()->getCountry() <= f2.getDest()->getCountry();
}

/**
 * @brief Boolean function to order flights by airport code
 * @param f1
 * @param f2
 */
bool Flight::byAirlineCode(Flight f1, Flight f2) {
    return f1.getAirline()->getCode() <= f2.getAirline()->getCode();
}
