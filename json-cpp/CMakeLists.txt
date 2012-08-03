project(JSONCPP)
include_directories(include)
cmake_minimum_required(VERSION 2.6)

add_library(jsoncpp SHARED json_reader.cpp json_value.cpp json_writer.cpp)

install(TARGETS jsoncpp LIBRARY DESTINATION lib)

