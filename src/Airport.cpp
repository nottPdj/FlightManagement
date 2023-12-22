#include "Airport.h"

Airport::Airport(std::string code,std::string name,std::string city,std::string country,std::string latitude,std::string longitude){
    this->code=code;
    this->name=name;
    this->city=city;
    this->country=country;
    this->latitude=latitude;
    this->longitude=longitude;
}

void Airport::addFlight(Flight flight) {
    flights.push_back(flight);
}

std::string Airport::getCode() const {
    return this->code;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCity() const {
    return city;
}

std::string Airport::getCountry() const {
    return country;
}

std::string Airport::getLatitude() const {
    return latitude;
}

std::string Airport::getLongitude() const {
    return longitude;
}

bool Airport::byCode(Airport *a1, Airport *a2) {
    return a1->getCode() <= a2->getCode();
}

bool Airport::byName(Airport *a1, Airport *a2) {
    return a1->getName() <= a2->getName();
}

bool Airport::byCity(Airport *a1, Airport *a2) {
    return a1->getCity() <= a2->getCity();
}

bool Airport::byCountry(Airport *a1, Airport *a2) {
    return a1->getCountry() <= a2->getCountry();
}

bool Airport::byLatitude(Airport *a1, Airport *a2) {
    return a1->getLatitude() <= a2->getLatitude();
}

bool Airport::byLongitude(Airport *a1, Airport *a2) {
    return a1->getLongitude() <= a2->getLongitude();
}

void Airport::setVisited(bool v) {
    this->visited=v;
}

bool Airport::isVisited() const {
    return visited;
}

bool Airport::isProcessing() const {
    return processing;
}

void Airport::setProcessing(bool p) {
    this->processing=p;
}

std::vector<Flight> Airport::getFlights() {
    return flights;
}

