#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    this->code=code;
    this->name=name;
    this->callsign=callsign;
    this->country=country;
}

std::string Airline::getCode() const {
    return code;
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}



bool Airline::byCode(Airline *a1, Airline *a2) {
    return a1->getCode() <= a2->getCode();
}

bool Airline::byName(Airline *a1, Airline *a2) {
    return a1->getName() <= a2->getName();
}

bool Airline::byCallsign(Airline *a1, Airline *a2) {
    return a1->getCallsign() <= a2->getCallsign();
}

bool Airline::byCountry(Airline *a1, Airline *a2) {
    return a1->getCountry() <= a2->getCountry();
}

