#include "Airport.h"

/**
 * @brief Constructor of  Airport
 * @param code
 * @param name
 * @param city
 * @param country
 * @param latitude
 * @param longitude
 */
Airport::Airport(std::string code,std::string name,std::string city,std::string country,std::string latitude,std::string longitude){
    this->code=code;
    this->name=name;
    this->city=city;
    this->country=country;
    this->latitude=latitude;
    this->longitude=longitude;
}

/**
 * @brief Adds a flight to the airport
 * @param flight
 */
void Airport::addFlight(Flight flight) {
    flights.push_back(flight);
}

/**
 * @brief Gets the code of the airport
 * @return code
 */
std::string Airport::getCode() const {
    return this->code;
}

/**
 * @brief Gets the name of the airport
 * @return name
 */
std::string Airport::getName() const {
    return name;
}

/**
 * @brief Gets the city where the airport is located
 * @return city
 */
std::string Airport::getCity() const {
    return city;
}

/**
 * @brief Gets the country where the airport is located
 * @return country
 */
std::string Airport::getCountry() const {
    return country;
}

/**
 * @brief Gets the latitude of the airport
 * @return latitude
 */
std::string Airport::getLatitude() const {
    return latitude;
}

/**
 * @brief Gets the longitude of the airport
 * @return longitude
 */
std::string Airport::getLongitude() const {
    return longitude;
}

/**
 * @brief Boolean function to order airports by code
 * @param a1
 * @param a2
 */
bool Airport::byCode(Airport *a1, Airport *a2) {
    return a1->getCode() < a2->getCode();
}
/**
 * @brief Boolean function to order airports by name
 * @param a1
 * @param a2
 */
bool Airport::byName(Airport *a1, Airport *a2) {
    return a1->getName() < a2->getName();
}
/**
 * @brief Boolean function to order airports by city
 * @param a1
 * @param a2
 */
bool Airport::byCity(Airport *a1, Airport *a2) {
    return a1->getCity() < a2->getCity();
}
/**
 * @brief Boolean function to order airports by country
 * @param a1
 * @param a2
 */
bool Airport::byCountry(Airport *a1, Airport *a2) {
    return a1->getCountry() < a2->getCountry();
}
/**
 * @brief Boolean function to order airports by latitude
 * @param a1
 * @param a2
 */
bool Airport::byLatitude(Airport *a1, Airport *a2) {
    return std::stod(a1->getLatitude()) < std::stod(a2->getLatitude());
}
/**
 * @brief Boolean function to order airports by longitude
 * @param a1
 * @param a2
 */
bool Airport::byLongitude(Airport *a1, Airport *a2) {
    return std::stod(a1->getLongitude()) < std::stod(a2->getLongitude());
}
/**
 * @brief Boolean function to order airports by the number of flights out
 * @param a1
 * @param a2
 */
bool Airport::byNFlightsOut(Airport *a1, Airport *a2) {
    return a1->getNFlightsOut() < a2->getNFlightsOut();
}

/**
 * @brief Sets the airport (vertex) to visited or not
 * @param v
 */
void Airport::setVisited(bool v) {
    this->visited=v;
}

/**
 * @brief Checks if the airport (vertex) is visited
 */
bool Airport::isVisited() const {
    return visited;
}

/**
 * @brief Checks if the airport (vertex) is processing
 */
bool Airport::isProcessing() const {
    return processing;
}

/**
 * @brief Sets the airport (vertex) to processing or not
 * @param p
 */
void Airport::setProcessing(bool p) {
    this->processing=p;
}

/**
 * @brief Gets the flights out of the airport
 * @return flights
 */
std::vector<Flight> Airport::getFlights() {
    return flights;
}

/**
 * @brief Gets the max trip distance from the airport
 * @return maxTripDistance
 */
int Airport::getMaxTripDistance() const {
    return maxTripDistance;
}

/**
 * @brief Sets the max trip distance a certain value
 * @param distance
 */
void Airport::setMaxTripDistance(int distance) {
    maxTripDistance = distance;
}

/**
 * @brief Gets the various destinations from the max trip of the airport
 * @return maxTripDests
 */
std::vector<Airport *> Airport::getMaxTripDests() const {
    return maxTripDests;
}

/**
 * @brief Adds a destination to the max trip
 * @param dest
 */
void Airport::addMaxTripDest(Airport *dest) {
    maxTripDests.push_back(dest);
}

/**
 * @brief Gets the number of flights out
 */
int Airport::getNFlightsOut() const {
    return (int)this->flights.size();
}

/**
 * @brief Sets the number of the airport (vertex)
 * @param i
 */
void Airport::setNum(int i) {
    num=i;
}

/**
 * @brief Sets the low of the airport (vertex)
 * @param i
 */
void Airport::setLow(int i) {
    low=i;
}

/**
 * @brief Gets the number of the airport (vertex)
 */
int Airport::getNum() const {
    return num;
}

/**
 * @brief Sets the low of the airport (vertex)
 */
int Airport::getLow() const {
    return low;
}
