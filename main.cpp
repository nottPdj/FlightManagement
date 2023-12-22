#include <iostream>
#include "src/Graph.h"
#include "src/Terminal.h"
#include "src/Auxiliar.h"

int main() {
    Graph g=Graph();
    Auxiliar::readAirports(g);
    Auxiliar::readFlights(g);
    Auxiliar::readAirlines(g);
    Terminal terminal = Terminal(g);
    terminal.run();
    return 0;
}
