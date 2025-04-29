cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

add_executable(my_app src/main.cpp)

target_link_libraries(my_app PRIVATE nlohmann_json::nlohmann_json)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(MyProject PRIVATE cpr::cpr)