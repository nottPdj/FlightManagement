#include "Airline.h"

/**
 *@brief Constructor of Airline
 * @param code
 * @param name
 * @param callsign
 * @param country
 */
Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    this->code=code;
    this->name=name;
    this->callsign=callsign;
    this->country=country;
}

/**
 * @brief Gets the code of a airline
 * @return code
 */
std::string Airline::getCode() const {
    return code;
}

/**
 * @brief Gets the name of a airline
 * @return name
 */
std::string Airline::getName() const {
    return name;
}

/**
 * @brief Gets the callsign of a airline
 * @return callsign
 */
std::string Airline::getCallsign() const {
    return callsign;
}

/**
 * @brief Gets the country which the airline belongs
 * @return country
 */
std::string Airline::getCountry() const {
    return country;
}

/**
 * @brief Boolean function to order airlines by code
 * @param a1
 * @param a2
 */
bool Airline::byCode(Airline *a1, Airline *a2) {
    return a1->getCode() < a2->getCode();
}

/**
 * @brief Boolean function to order airlines by name
 * @param a1
 * @param a2
 */
bool Airline::byName(Airline *a1, Airline *a2) {
    return a1->getName() < a2->getName();
}

/**
 * @brief Boolean function to order airlines by callsign
 * @param a1
 * @param a2
 */
bool Airline::byCallsign(Airline *a1, Airline *a2) {
    return a1->getCallsign() < a2->getCallsign();
}

/**
 * @brief Boolean function to order airlines by country
 * @param a1
 * @param a2
 */
bool Airline::byCountry(Airline *a1, Airline *a2) {
    return a1->getCountry() < a2->getCountry();
}

