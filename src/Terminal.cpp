#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cmath>
#include <utility>
#include "Terminal.h"

/**
 * @brief Constructor of the Terminal class. Stores the graph containing all air travel information in the private field
 * so that it can communicate with it throughout the program.
 * @param g Graph containing all air travel information being managed by the Terminal
 */
Terminal::Terminal(const Graph &g) {
    this->g = g;
}

/**
 * @brief This method is called to start the interface.
 */
void Terminal::run(){
    system("clear");
    printMainMenu();
    system("clear");
}

/**
 * @brief Prints the main menu.
 */
void Terminal::printMainMenu() {
    system("clear");
    std::cout << center("AIR TRAVEL FLIGHT", '*', MENU_WIDTH) << "\n\n"
              << "\t0 - Consult airports" << "\n"
              << "\t1 - Consult flights" << "\n"
              << "\t2 - Consult airlines" << "\n"
              << "\t3 - Flights from an airport" << "\n"
              << "\t4 - Flights per city" << "\n"
              << "\t5 - Flights per airline" << "\n"
              << "\t6 - Destinations from an airport" << "\n"
              << "\t7 - Reachable destinations from an airport in a maximum n lay-overs" << "\n"
              << "\t8 - Maximum trip (with the greatest number of lay-overs)" << "\n"
              << "\t9 - Top airports with the greatest air traffic capacity" << "\n"
              << "\t10 - Essential airports to the network’s circulation capability" << "\n"
              << "\t11 - Consult the best flight option" << "\n";

    printExit();
    std::cout << "Press the number corresponding the action you want." << "\n";
    waitMenu();
}

/**
 * @brief Waits for the input and depending on it, calls the method responsible for accomplishing what was asked.
 */
void Terminal::waitMenu(){
    std::string choice;
    std::cin >> choice;             // Fetch the option chosen
    if (choice == "q")              // Quit
        return;
    system("clear");
    printingOptions options;
    switch (stoi(choice)) {
        // Consult airports
        case 0: {
            options.message = "Global view of the airports\n";
            printAirportsList(g.getAirports(), options);
            break;
        }
        // Consult flights
        case 1: {
            options.message = "Global view of the flights\n";
            printFlightsList(g.getFlights(), options);
            break;
        }
        // Consult airlines
        case 2: {
            options.message = "Global view of the airlines\n";
            printAirlinesList(g.getAirlines(), options);
            break;
        }
        // Flights from an airport
        case 3: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            system("clear");
            options.message = "Flights from airport " + code + "\n";
            printFlightsList(g.getFlightsFromAirport(code), options);
            break;
        }
        // Flights per city
        case 4: {
            std::cout << "Enter the city name: ";
            std::string city;
            std::cin >> city;        // Fetch city
            system("clear");
            options.message = "Flights from " + city + "\n";
            printFlightsList(g.getFlightsFromCity(city), options);
            break;
        }
        // Flights per airline
        case 5: {
            std::cout << "Enter the airline code: ";
            std::string airline;
            std::cin >> airline;        // Fetch country
            system("clear");
            options.message = "Flights with " + airline + "\n";
            printFlightsList(g.getFlightsPerAirline(airline), options);
            break;
        }
        // Destinations from an airport
        case 6: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            getDestinations(code);
            break;
        }
        // Reachable destinations from an airport in a maximum n lay-overs
        case 7: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            std::cout << "Enter the maximum number of lay-overs: ";
            int stops;
            std::cin >> stops;        // Fetch max number of lay-overs
            getDestinations(code, stops);
            break;
        }
        // Maximum trip (with the greatest number of lay-overs)
        case 8: {
            options.sort = false;
            options.showSortingOptions = false;
            std::vector<Flight> maxTrip = g.getMaxTrip();
            options.message = "Maximum trip available (with the greatest number of lay-overs): " + to_string(maxTrip.size() - 1) + "lay-overs\n";
            printFlightsList(maxTrip, options);
            break;
        }
        // Airports with the greatest air traffic capacity
        case 9: {
            std::cout << "Display Top-";
            int top;
            std::cin >> top;
            options.message = "Top-" + to_string(top) + " airports with the greatest air traffic capacity\n";
            // TODO cortar para ficar só com o top-k ou vêm só k da funcao?
            printAirportsList(g.getGreatestNumFlights(), options);
            break;
        }
        // Essential airports to the network’s circulation capability
        case 10: {
            string message = "Essential airports to the network's circulation capability\n";
            printAirportsList(g.getEssentialAirports(), options);
            break;
        }
        // Consult the best flight option
        case 11: {
            std::cout << "FROM\n";
            std::cout << "Search by: \n"
                << "\t0 - Airport code\n"
                << "\t1 - Airport name\n"
                << "\t2 - City\n"
                << "\t3 - Geographical coordinates (lat, lon)\n";
            int searchFrom;
            std::string source;
            std::cin >> searchFrom;
            system("clear");
            std::cout << "From: ";
            std::cin >> source;

            std::cout << "TO\n";
            std::cout << "Search by: \n"
                      << "\t0 - Airport code\n"
                      << "\t1 - Airport name\n"
                      << "\t2 - City\n"
                      << "\t3 - Geographical coordinates (lat, lon)\n";
            int searchTo;
            std::string dest;
            std::cin >> searchTo;
            system("clear");
            std::cout << "To: ";
            std::cin >> dest;

            options.message = "Best flight option(s) from " + source + " to " + dest;

            std::cout << "Airline Preferences\n"
                << "\t0 - Maximum number of different airlines"
                << "\t1 - Travel only in specific airlines"
                << "\t2 - No preferences";
            int preference = 2;
            std::cin >> preference;
            system("clear");

            int maxAirlines = -1;
            vector<std::string> airlineCodes;

            if (preference == 0) {
                std::cout << "Maximum number of different airlines: ";
                std::cin >> maxAirlines;
                options.message += " in a maximum of " + to_string(maxAirlines) + " airlines";
            } else if (preference == 1) {
                std::cout << "List the airlines to use by code (Separated by ENTER, 'done' when all are listed): \n";
                std::string airline;
                while (true) {
                    std::cin >> airline;
                    if (airline == "code") {
                        break;
                    }
                    airlineCodes.push_back(airline);
                }
                options.message += " using only the specified airlines";
            }
            options.message += "\n";
            printFlightsLists(g.getBestOption(source, searchFrom, dest, searchTo, maxAirlines, airlineCodes), options);
        }
        default: {
            printMainMenu();
        }
    }
}


void Terminal::getDestinations(std::string code, int stops) {
    std::cout << "Choose how to display destinations: \n"
        << "\t0 - Airports\n"
        << "\t1 - Cities\n"
        << "\t2 - Countries\n";
    int option;
    std::cin >> option;
    system("clear");
    printingOptions options;
    if (stops == 0) {
        options.message = "Destinations from the airport " + code + "\n";
    } else {
        options.message = "Reachable destinations from the airport " + code + " in a maximum of " + to_string(stops) + " lay-overs\n";
    }
    switch (option) {
        case 0:
            printAirportsList(g.getReachableAirportsFrom(code, stops), options);
            break;
        case 1:
            printCitiesList(g.getReachableCitiesFrom(code, stops), options);
            break;
        case 2:
            printCountriesList(g.getReachableCountriesFrom(code, stops), options);
            break;
    }
}



void Terminal::printAirlinesList(std::vector<Airline *> airlines, printingOptions options) {
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << airlines.size() << " airlines\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("Callsign", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortAirlinesList(airlines, options.sortOptions);

    // AIRLINES
    for (Airline *airline : airlines) {
        std::cout << "|" << center(airline->getCode(), ' ', CODE_WIDTH) << "|" << center(airline->getName(), ' ', NAME_WIDTH) << "|"
                  << center(airline->getCallsign(), ' ', DEFAULT_WIDTH) << "|" << center(airline->getCountry(), ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printAirlinesList(airlines, options);
        }
    }
}

void Terminal::printAirportsList(std::vector<Airport*> airports, printingOptions options) {
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << airports.size() << " airports\n";
    std::cout << "\n";

   // HEADERS
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("City", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|"
              << center("Latitude", ' ', DEFAULT_WIDTH) << "|" << center("Longitude", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortAirportsList(airports, options.sortOptions);

    // AIRPORTS
    for (Airport *airport : airports) {
        std::cout << "|" << center(airport->getCode(), ' ', CODE_WIDTH) << "|" << center(airport->getName(), ' ', NAME_WIDTH) << "|"
                  << center(airport->getCity(), ' ', DEFAULT_WIDTH) << "|" << center(airport->getCountry(), ' ', DEFAULT_WIDTH) << "|"
                  << center(airport->getLatitude(), ' ', DEFAULT_WIDTH) << "|" << center(airport->getLongitude(), ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH)
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printAirportsList(airports, options);
        }
    }
}


void Terminal::printFlightsList(std::vector<Flight> flights, printingOptions options) {
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << flights.size() << " flights\n";
    std::cout << "\n";

    // HEADERS: FROM and TO and AIRLINE
    std::cout << "|" << fill('-', (CODE_WIDTH + DEFAULT_WIDTH * 2) * 2 + CODE_WIDTH + 8) << "|\n";

    std::cout << "| FROM" << fill(' ', CODE_WIDTH + DEFAULT_WIDTH * 2 + 2 - 5) << "|"
                << "| TO" << fill(' ', CODE_WIDTH + DEFAULT_WIDTH * 2 + 2 - 3) << "|"
                << "| AIRLINE" << fill(' ', DEFAULT_WIDTH - 8) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFAULT_WIDTH)
                  << fill('-', DEFAULT_WIDTH) << "|\n";
    }
    std::cout << "|" << fill('-', CODE_WIDTH) << "|\n";

    // SECONDARY HEADERS
    for (int i = 0; i < 2; i++) {
        std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("City", ' ', DEFAULT_WIDTH) << "|"
                  << center("Country", ' ', DEFAULT_WIDTH) << "|";
    }
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFAULT_WIDTH)
                  << fill('-', DEFAULT_WIDTH) << "|\n";
    }
    std::cout << "|" << fill('-', CODE_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortFlightsList(flights, options.sortOptions);

    // FLIGHTS
    for (Flight flight : flights) {
        std::cout << "|" << center(flight.getSource()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getSource()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getSource()->getCountry(), ' ', DEFAULT_WIDTH) << "|"
                    << "|" << center(flight.getDest()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getDest()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getDest()->getCountry(), ' ', DEFAULT_WIDTH) << "|"
                    << "|" << center(flight.getAirline().getCode()) << "|\n";
    }

    // CLOSING TABLE
    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', DEFAULT_WIDTH)
                  << fill('-', DEFAULT_WIDTH) << "|\n";
    }
    std::cout << "|" << fill('-', CODE_WIDTH) << "|\n";

    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printFlightsList(flights, options);
        }
    }
}


void Terminal::printCitiesList(std::vector<std::string> cities, printingOptions options) {
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << cities.size() << " cities\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("City", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortCitiesList(cities, options.sortOptions);

    // CITIES
    for (std::string city : cities) {
        std::cout << "|" << center(city, ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printCitiesList(cities, options);
        }
    }
}

void Terminal::printCountriesList(std::vector<std::string> countries, printingOptions options) {
    if (options.printMessage)
        std::cout << options.message;
    if (options.printCountMessage)
        std::cout << "There are " << countries.size() << " countries\n";
    std::cout << "\n";

    // HEADERS
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortCountriesList(countries, options.sortOptions);

    // COUNTRIES
    for (std::string country : countries) {
        std::cout << "|" << center(country, ' ', DEFAULT_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', DEFAULT_WIDTH) << "|\n";

    if (options.showSortingOptions)
        printSortingOptions();
    if (options.showEndMenu)
        endDisplayMenu();
    if (options.getInput) {
        if (getInput() == 's') {
            getSortingOptions(options.sortOptions);
            printCountriesList(countries, options);
        }
    }
}


void Terminal::printFlightsLists(std::vector<std::vector<Flight>> flightsLists, printingOptions options) {

    for (auto flightsList : flightsLists) {
        if ()
    }
}




/**
 * @brief Returns a string with c repeated width times.
 * @param c Character to fill with
 * @param width Width of the string
 * @return String with length width filled with c
 */
std::string Terminal::fill(char c, int width) {
    std::ostringstream oss;
    oss << std::setw(width) << std::setfill(c) << "";
    return oss.str();
}


/**
 * @brief Return a string of length width with str centered and surrounded by sep.
 * @param str
 * @param sep
 * @param width
 * @return String of length width with str centered and surrounded by sep
 */
std::string Terminal::center(const std::string &str, char sep, int width) {
    std::ostringstream oss;
    int space = (width - str.length()) / 2;
    std::cout << std::setw(space) << std::setfill(sep) << "" << str << std::setw(width - str.length() - space) << std::setfill(sep) << "";
    return oss.str();
}



void Terminal::printBackToMenu() {
    std::cout << "Press 'm' to go back to the main menu.\n";
}

void Terminal::printSortingOptions() {
    std::cout << "Press 's' for sorting options.\n";
}

/**
 * @brief Receives the sorting options from the user.
 * @param sortOptions Struct where the sorting options will be stored
 */
void Terminal::getSortingOptions(sortingOptions &sortOptions) {
    std::cout << "SORTING OPTIONS\n\n";
    std::cout << "Type the number of the column (starting at 0) to order by: ";
    std::cin >> sortOptions.orderBy;
    std::cout << "Type 0 for descending order or 1 for ascending order: ";
    std::cin >> sortOptions.ascending;
}


void Terminal::printExit() {
    std::cout << "Press 'q' to quit.\n";
}

/**
 * @brief Receives input from the user.
 * @return
 */
char Terminal::getInput() {
    char input;
    std::cin >> input;
    if (input == 'm') {
        printMainMenu();
    }
    return input;
}

/**
 * @brief Prints default menu after displaying anything that allows to go back to the main menu or exit the program.
 */
void Terminal::endDisplayMenu() {
    std::cout << "\n\n";
    printBackToMenu();
    printExit();
}

void Terminal::sortAirportsList(vector<Airport *> &airports, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByCode);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByName);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByName);
        case 2:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByCity);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByCity);
        case 3:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByCountry);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByCountry);
        case 4:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByLatitude);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByLatitude);
        case 5:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), airportsByLongitude);
            else
                std::sort(airports.rbegin(), airports.rend(), airportsByLongitude);
    }
}

void Terminal::sortAirlinesList(vector<Airline *> &airlines, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), airlinesByCode);
            else
                std::sort(airlines.rbegin(), airlines.rend(), airlinesByCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), airlinesByName);
            else
                std::sort(airlines.rbegin(), airlines.rend(), airlinesByName);
        case 2:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), airlinesByCallsign);
            else
                std::sort(airlines.rbegin(), airlines.rend(), airlinesByCallsign);
        case 3:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), airlinesByCountry);
            else
                std::sort(airlines.rbegin(), airlines.rend(), airlinesByCountry);
    }
}

void Terminal::sortFlightsList(vector<Flight> &flights, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsBySourceCode);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsBySourceCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsBySourceCity);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsBySourceCity);
        case 2:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsBySourceCountry);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsBySourceCountry);
        case 3:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsByDestCode);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsByDestCode);
        case 4:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsByDestCity);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsByDestCity);
        case 5:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsByDestCountry);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsByDestCountry);
        case 6:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), flightsByAirlineCode);
            else
                std::sort(flights.rbegin(), flights.rend(), flightsByAirlineCode);
    }
}

void Terminal::sortCitiesList(vector<std::string> &cities, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(cities.begin(), cities.end(), citiesByName);
            else
                std::sort(cities.rbegin(), cities.rend(), citiesByName);
    }
}

void Terminal::sortCountriesList(vector<std::string> &countries, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(countries.begin(), countries.end(), countriesByName);
            else
                std::sort(countries.rbegin(), countries.rend(), countriesByName);
    }
}



