cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(configuration_reader LANGUAGES CXX)

include_directories(configuration_file)
include_directories(configuration)
include_directories(parsers)
include_directories(test)

file(GLOB load_and_save_SRC
     "configuration/Configuration.cpp"
     "configuration/Configuration.hpp"
     "configuration_file/ConfigurationFile.cpp"  
     "configuration_file/ConfigurationFile.hpp"
     "parsers/DefaultParser.cpp"
     "parsers/DefaultParser.hpp"
     "parsers/ParserInterface.hpp"
     "tests/load_and_save.cpp"
)


add_custom_target(load_and_save)
add_executable(load_and_save_test ${load_and_save_SRC})
add_dependencies(load_and_save load_and_save_test)