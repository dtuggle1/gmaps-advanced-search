#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <cpr/cpr.h>
using json = nlohmann::json;

class Filters {
    private:
        std::string keyword;
        float min_rating;
        std::string location_latitude;
        std::string location_longittude;
        float distance;
        int min_reviews;
        std::string price;
        std::string open_hour;
        json primary_search_filters;

        // json object data type

        void loadJsonFromFile(const std::string& filename){
            std::ifstream file(filename);
            if (!file.is_open()){
                throw std::runtime_error("Couldnt open file");
            }
            json json_file;
            file >> json_file;

            keyword = json_file.at("keyword").get<std::string>();
            min_rating = json_file.at("min_rating").get<int>();
            location_latitude = json_file.at("location_latitude").get<std::string>();
            location_longitude = json_file.at("location_longitude").get<std::string>();
            distance = json_file.at("distance").get<float>();
            min_reviews = json_file.at("min_reviews").get<int>();
            price = json_file.at("price").get<std::string>();
            open_hour = json_file.at("open_hour").get<std::string>();
        }
        void primarySearchFilters(){
            
            std::string coordinates = std::format("{},{}", location_latitude, location_longittude);
            // todo: change payload vars to the correct ones per the api
            json payload = {
                {"keyword", this->keyword},
                {"coordinates", coordinates}, 
                {"distance", this->distance}
            }
            primary_search_filters = payload;
        }
    public:
        Filters(const std::string& filename){
            loadJsonFromFile(filename);
            primarySearchFilters();
        }
        json getPrimarySearchFilters(){
            return primary_search_filters;
        }
}

json primarySearch(Filters filters){
    std::string url;
    std::string payload;
    url = "https://serpapi.com/searches/625535ed92cebc19/6807b9b6a919a9218a7d85e7.json"
    std::cout << "Attempting to Access API" << "\n";
    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{filters->payload.dump()}
    );
    std::cout << "Status" << response.status_code << "\n";
    std::cout << "Response" << response.text << "\n";

    // todo: convert output to json type

    json output;
    return output
    
}

// All filters and ordering preferences come in via json block

// Primary filters used for initial search

// Rest API call to Google Maps API -> results come in via JSON

// Results are parsed and organized

// Secondary and primary filters used for fine-tune searching

// Send results to front-end

int main() {
    std:: string filename = "sample-filters.json";
    Filters filters(filename);



}