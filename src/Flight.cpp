#include "Flight.h"

Flight::Flight(Airport* source, Airport* dest, Airline* airline) {
    this->source=source;
    this->dest=dest;
    this->airline=airline;
}
