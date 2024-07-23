/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once

#include <sstream>
#include <map>

#define default_section "default";
using map_of_maps = std::map<std::string, std::map<std::string, std::string>>;
using insertion_vector = std::vector<std::string>;

// Takes a stringstream in input and ensures 
// template<class T>
class ParserInterface
{
public:
    virtual std::pair<insertion_vector, map_of_maps> deserialize(const std::stringstream& ss) = 0;
    virtual std::stringstream serialize(const std::pair<insertion_vector, map_of_maps>& data) = 0;
};