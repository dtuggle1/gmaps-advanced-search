#ifndef FILTERS_API_HANDLER_H
#define FILTERS_API_HANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

extern bool CALL_API;

// Loads a JSON file from disk
json loadJsonFromFile(std::string& filename);

class Filters {
private:
    void parseJsonFile(json json_file);

public:
    std::string keyword;
    float min_rating;
    std::string location_latitude;
    std::string location_longitude;
    float distance;
    int min_reviews;
    std::string price;
    std::string open_hour;

    Filters(std::string& filename);

    json payload() const;
};

// Makes the primary search call to SerpAPI
json primarySearch(const Filters& filters);

// Filters results returned from SerpAPI
json fineSearch(const Filters& filters, json api_output);

#endif // FILTERS_API_HANDLER_H
