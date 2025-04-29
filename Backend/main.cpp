#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <cpr/cpr.h>
using json = nlohmann::json;

bool CALL_API=true;

json loadJsonFromFile(std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Couldnt open file");
    }
    json json_file;
    file >> json_file;
    return json_file;
}

class Filters {
    private:
        // json object data type

        void parseJsonFile(json json_file){
            keyword = json_file.at("keyword").get<std::string>();
            min_rating = json_file.at("min_rating").get<int>();
            location_latitude = json_file.at("location_latitude").get<std::string>();
            location_longitude = json_file.at("location_longitude").get<std::string>();
            distance = json_file.at("distance").get<float>();
            min_reviews = json_file.at("min_reviews").get<int>();
            price = json_file.at("price").get<std::string>();
            open_hour = json_file.at("open_hour").get<std::string>();
        }
    public:
        std::string keyword;
        float min_rating;
        std::string location_latitude;
        std::string location_longittude;
        float distance;
        int min_reviews;
        std::string price;
        std::string open_hour;

        Filters(std::string& filename){
            json filters_input;
            filters_input = loadJsonFromFile(filename);
            parseJsonFile(filters_input);
        }

}

json primarySearch(Filters filters){
    std::string url;
    std::string payload;
    
    url = std::format("https://serpapi.com/search.json?engine=google_maps&q={}&ll=@{},{},15.1z&type=search&api_key={}", //convert zoom level to distance
    filters->keyword,
    filters->latitude,
    filters->longtitude,
    std::getenv("SERP_DTUGGLE1_API_KEY");
    )
    std::cout << "Attempting to Access API" << "\n";
    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{filters->payload.dump()}
    );
    std::cout << "Status" << response.status_code << "\n";
    std::cout << "Response" << response.text << "\n";

    json search_results = nlohmann::json::parse(response.text);
    return search_results;   
}

json fineSearch(Filters filters, json api_output){
    json results = api_output["local_results"];
    for (auto it results.begin(); results.end()){
        if ((*it)["rating"] < filters.min_rating){
            it = results.erase(it);
        }
        else {
            ++it;
        }
    }
    return results;
}
// All filters and ordering preferences come in via json block

// Primary filters used for initial search

// Rest API call to Google Maps API -> results come in via JSON

// Results are parsed and organized

// Secondary and primary filters used for fine-tune searching

// Send results to front-end

int main() {
    json api_output;
    json results;
    std:: string sample_filters_filename = "sample-filters.json";
    Filters filters(sample_filters_filename);
    if CALL_API {
        api_output = primarySearch(filters);
    }
    else {
        api_output = loadJsonFromFile("serp-api-sample.json");
    }
    results = fineSearch(filters, api_output);
    std::ofstream file("output.json");
    file << api_output.dump(4); 

}