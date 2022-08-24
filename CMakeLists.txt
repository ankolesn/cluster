cmake_minimum_required(VERSION 3.22)
project(cluster)

set(CMAKE_CXX_STANDARD 17)
find_package(Crow)
find_package(InfluxDB)
add_executable(${PROJECT_NAME} main.cpp Data.cpp Data.h)
target_link_libraries(${PROJECT_NAME} PUBLIC Crow::Crow)
target_link_libraries(${PROJECT_NAME} PRIVATE InfluxData::InfluxDB)
