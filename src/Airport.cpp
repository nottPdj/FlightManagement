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
