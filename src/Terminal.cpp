#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
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
              << "\t0 - Global numbers" << "\n"
              << "\t1 - Flights from an airport" << "\n"
              << "\t2 - Flights per city" << "\n"
              << "\t3 - Flights per airline" << "\n"
              << "\t4 - Countries that an airport flies to" << "\n"
              << "\t5 - Countries that a city flies to" << "\n"
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
        // Global numbers
        case 0: {
            std::cout << "Global numbers\n\n";
            std::cout << "There are " + std::to_string(g.getNumAirports()) + " airports\n";
            std::cout << "There are " + std::to_string(g.getNumFlights()) + " flights\n";
            std::cout << "There are " + std::to_string(g.getNumAirlines()) + " airlines\n";
            endDisplayMenu();
            getInput();
            break;
        }
        // Flights from an airport
        case 1: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            system("clear");
            std::pair<int, int> nums = g.getNumFlightsFromAirport(code);
            std::cout << "There are " + std::to_string(nums.first) + " flights from airport " + code + "\n";
            std::cout << "From " + std::to_string(nums.second) + " different airlines\n";
            endDisplayMenu();
            getInput();
            break;
        }
        // Flights per city
        case 2: {
            std::cout << "Enter the city name: ";
            std::string city;
            std::cin >> city;        // Fetch city
            system("clear");
            std::cout << "There are " + std::to_string(g.getNumFlightsFromCity(city)) + " flights from " + city + "\n";
            endDisplayMenu();
            getInput();
            break;
        }
        // Flights per airline
        case 3: {
            std::cout << "Enter the airline code: ";
            std::string airline;
            std::cin >> airline;        // Fetch country
            system("clear");
            std::cout << "There are " + std::to_string(g.getNumFlightsPerAirline(airline)) + " flights from " + airline + "\n";
            endDisplayMenu();
            getInput();
            break;
        }
        // Countries that an airport flies to
        case 4: {
            std::cout << "Enter the airport code: ";
            std::string code;
            std::cin >> code;        // Fetch airport code
            options.message = "Countries that airport " + code + " flies to\n";
            printCountriesList(g.getReachableCountriesFrom(code, 0), options);
            break;
        }
        // Countries that a city flies to
        case 5: {
            std::cout << "Enter the city name: ";
            std::string city;
            std::cin >> city;        // Fetch city
            options.message = "Countries that " + city + " flies to\n";
            printCountriesList(g.getCountriesFromCity(city), options);
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
            std::vector<std::vector<Flight>> maxTrips = g.getMaxTrip();
            /*options.message = "Maximum trip available (with the greatest number of lay-overs): " + std::to_string(maxTrip.size() - 1) + "lay-overs\n";
            printFlightsList(maxTrip, options);*/
            printFlightsLists(maxTrips, options);
            break;
        }
        // Airports with the greatest air traffic capacity
        case 9: {
            std::cout << "Display Top-";
            int top;
            std::cin >> top;
            options.message = "Top-" + std::to_string(top) + " airports with the greatest air traffic capacity\n";
            // TODO cortar para ficar só com o top-k ou vêm só k da funcao?
            printAirportsList(g.getGreatestNumFlights(), options);
            break;
        }
        // Essential airports to the network’s circulation capability
        case 10: {
            options.message = "Essential airports to the network's circulation capability\n";
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
            std::vector<std::string> airlineCodes;

            if (preference == 0) {
                std::cout << "Maximum number of different airlines: ";
                std::cin >> maxAirlines;
                options.message += " in a maximum of " + std::to_string(maxAirlines) + " airlines";
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
        options.message = "Reachable destinations from the airport " + code + " in a maximum of " + std::to_string(stops) + " lay-overs\n";
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
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("Callsign", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
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
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
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
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|\n";
    std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("Name", ' ', NAME_WIDTH) << "|"
              << center("City", ' ', DEFAULT_WIDTH) << "|" << center("Country", ' ', DEFAULT_WIDTH) << "|"
              << center("Latitude", ' ', NUMBER_WIDTH) << "|" << center("Longitude", ' ', NUMBER_WIDTH) << "|\n";
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortAirportsList(airports, options.sortOptions);

    // AIRPORTS
    for (Airport *airport : airports) {
        std::cout << "|" << center(airport->getCode(), ' ', CODE_WIDTH) << "|" << center(airport->getName(), ' ', NAME_WIDTH) << "|"
                  << center(airport->getCity(), ' ', DEFAULT_WIDTH) << "|" << center(airport->getCountry(), ' ', DEFAULT_WIDTH) << "|"
                  << center(airport->getLatitude(), ' ', NUMBER_WIDTH) << "|" << center(airport->getLongitude(), ' ', NUMBER_WIDTH) << "|\n";
    }

    // CLOSING TABLE
    std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
              << fill('-', DEFAULT_WIDTH) << "|" << fill('-', DEFAULT_WIDTH) << "|"
              << fill('-', NUMBER_WIDTH) << "|" << fill('-', NUMBER_WIDTH) << "|\n";

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
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "--" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "--" << fill('-', AIRLINE_WIDTH) << "|\n";

    std::cout << "|" << center("FROM", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|"
                << "|" << center("TO", ' ', (CODE_WIDTH + NAME_WIDTH * 2 + 2)) << "|"
                << "|" << center("AIRLINE", ' ', AIRLINE_WIDTH) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "|" << fill('-', AIRLINE_WIDTH) << "|\n";

    // SECONDARY HEADERS
    for (int i = 0; i < 2; i++) {
        std::cout << "|" << center("Code", ' ', CODE_WIDTH) << "|" << center("City", ' ', NAME_WIDTH) << "|"
                  << center("Country", ' ', NAME_WIDTH) << "|";
    }
    std::cout << "|" << center("Code", ' ', AIRLINE_WIDTH) << "|\n";

    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "|" << fill('-', NAME_WIDTH) << "|"
                  << fill('-', NAME_WIDTH) << "|";
    }
    std::cout << "|" << fill('-', AIRLINE_WIDTH) << "|\n";

    // SORTING
    if (options.sort)
        sortFlightsList(flights, options.sortOptions);

    // FLIGHTS
    for (Flight flight : flights) {
        std::cout << "|" << center(flight.getSource()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getSource()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getSource()->getCountry(), ' ', NAME_WIDTH) << "|"
                    << "|" << center(flight.getDest()->getCode(), ' ', CODE_WIDTH) << "|" << center(flight.getDest()->getCity(), ' ', NAME_WIDTH) << "|"
                  << center(flight.getDest()->getCountry(), ' ', NAME_WIDTH) << "|"
                    << "|" << center(flight.getAirline()->getCode(), ' ', AIRLINE_WIDTH) << "|\n";
    }

    // CLOSING TABLE
/*    for (int i = 0; i < 2; i++) {
        std::cout << "|" << fill('-', CODE_WIDTH) << "-" << fill('-', NAME_WIDTH) << "-"
                  << fill('-', NAME_WIDTH) << "-";
    }
    std::cout << "-" << fill('-', AIRLINE_WIDTH) << "|\n";*/
    std::cout << "|" << fill('-', (CODE_WIDTH + NAME_WIDTH * 2 + 4) * 2 + AIRLINE_WIDTH) << "|\n";

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
    options.sort = false;
    options.showSortingOptions = false;
    options.showEndMenu = false;
    options.getInput = false;
    for (int i = 0; i < flightsLists.size(); i++) {
        if (i == flightsLists.size() - 1) {
            options.showEndMenu = true;
            options.getInput = true;
        }
        printFlightsList(flightsLists[i], options);
        if (i == 0) {
            options.printMessage = false;
        }
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

void Terminal::sortAirportsList(std::vector<Airport *> &airports, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byCode);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byName);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byName);
        case 2:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byCity);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byCity);
        case 3:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byCountry);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byCountry);
        case 4:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byLatitude);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byLatitude);
        case 5:
            if (sortOptions.ascending)
                std::sort(airports.begin(), airports.end(), Airport::byLongitude);
            else
                std::sort(airports.rbegin(), airports.rend(), Airport::byLongitude);
    }
}

void Terminal::sortAirlinesList(std::vector<Airline *> &airlines, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), Airline::byCode);
            else
                std::sort(airlines.rbegin(), airlines.rend(), Airline::byCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), Airline::byName);
            else
                std::sort(airlines.rbegin(), airlines.rend(), Airline::byName);
        case 2:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), Airline::byCallsign);
            else
                std::sort(airlines.rbegin(), airlines.rend(), Airline::byCallsign);
        case 3:
            if (sortOptions.ascending)
                std::sort(airlines.begin(), airlines.end(), Airline::byCountry);
            else
                std::sort(airlines.rbegin(), airlines.rend(), Airline::byCountry);
    }
}

void Terminal::sortFlightsList(std::vector<Flight> &flights, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::bySourceCode);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::bySourceCode);
        case 1:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::bySourceCity);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::bySourceCity);
        case 2:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::bySourceCountry);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::bySourceCountry);
        case 3:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::byDestCode);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::byDestCode);
        case 4:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::byDestCity);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::byDestCity);
        case 5:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::byDestCountry);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::byDestCountry);
        case 6:
            if (sortOptions.ascending)
                std::sort(flights.begin(), flights.end(), Flight::byAirlineCode);
            else
                std::sort(flights.rbegin(), flights.rend(), Flight::byAirlineCode);
    }
}

void Terminal::sortCitiesList(std::vector<std::string> &cities, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(cities.begin(), cities.end());
            else
                std::sort(cities.rbegin(), cities.rend());
    }
}

void Terminal::sortCountriesList(std::vector<std::string> &countries, sortingOptions sortOptions) {
    switch(sortOptions.orderBy) {
        case 0:
            if (sortOptions.ascending)
                std::sort(countries.begin(), countries.end());
            else
                std::sort(countries.rbegin(), countries.rend());
    }
}



