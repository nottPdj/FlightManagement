#ifndef PROJETO2_AIRLINE_H
#define PROJETO2_AIRLINE_H


#include <string>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(std::string code,
            std::string name,
            std::string callsign,
            std::string country);
    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;


    static bool byCode(Airline *a1, Airline *a2);
    static bool byName(Airline *a1, Airline *a2);
    static bool byCallsign(Airline *a1, Airline *a2);
    static bool byCountry(Airline *a1, Airline *a2);
};


// Hash function for the Airline class
struct AirlineHash {
    std::size_t operator()(const Airline *airline) const {
        return std::hash<std::string>{}(airline->getCode());
    }
};

// Equality function for the Airport class
struct AirlineEqual {
    bool operator()(const Airline *lhs, const Airline *rhs) const {
        return lhs->getCode() == rhs->getCode();
    }
};


#endif //PROJETO2_AIRLINE_H
