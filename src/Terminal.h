#ifndef PROJETO2_TERMINAL_H
#define PROJETO2_TERMINAL_H

#include <string>
#include <vector>
#include "Graph.h"

/**
 * @brief Terminal auxiliar struct storing the sorting options of a table.
 */
struct sortingOptions {
    /**
     * Column, currently displaying, to order by
     */
    int orderBy = -1;
    bool ascending = true;
};



/**
 * @brief Terminal is used to create an interface between the user and the program.
 * Uses the console to output and to receive inputs. There are some functionalities available only for Ubuntu.
 * */
class Terminal {

private:
    /**
     * @brief Graph containing all the air travelling information that is being managed
     */
    Graph g;

    const static int MENU_WIDTH = 60;
    const static int CODE_WIDTH = 7;
    const static int NAME_WIDTH = 35;
    const static int DEFAULT_WIDTH = 20;


public:
    Terminal(const Graph &g);
    void run();

private:
    // Wait for inputs
    void waitMenu();
    char getInput();
    void getSortingOptions(sortingOptions &sortOptions);

    // Print menus
    void printMainMenu();
    void endDisplayMenu();
    void printBackToMenu();
    void printSortingOptions();
    void printExit();

    // Auxiliar formatting functions
    std::string fill(char c, int width);
    std::string center(const std::string &str, char sep, int width);

    void getDestinations(std::string code, int stops = 0);

    void printAirlinesList(std::vector<Airline> airlines);
    void printAirportsList(std::vector<Airport*> airports);
    void printFlightsList(std::vector<Flight> flights);
    void printCitiesList(std::vector<std::string> cities);
    void printCountriesList(std::vector<std::string> countries);
};


#endif //PROJETO2_TERMINAL_H
