cmake_minimum_required(VERSION 2.8)

project(HttpServer)

include_directories("${PROJECT_SOURCE_DIR}/include")
#add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_executable(httpserver ${PROJECT_SOURCE_DIR}/src/main.cc)
