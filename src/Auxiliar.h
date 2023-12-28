#ifndef PROJETO2_AUXILIAR_H
#define PROJETO2_AUXILIAR_H
#include "Graph.h"

/**
 * @brief Auxiliar is used to read the data files
 */
class Auxiliar {
public:
    static void readAirports(Graph& g);
    static void readAirlines(Graph& g);
    static void readFlights(Graph& g);

};


#endif //PROJETO2_AUXILIAR_H
