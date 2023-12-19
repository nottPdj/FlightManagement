#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include "Flight.h"

class Airport {
    info;                // contents
    vector<Flight> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;
    void addFlight(Airport *dest, double w);
    bool removeFlightTo(Airport *d);
public:
    Airport();
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Flight > &getAdj() const;
    void setAdj(const vector<Flight> &adj);
    friend class Graph;
};


#endif //PROJETO2_AIRPORT_H
