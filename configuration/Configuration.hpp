/*
/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once

#include <string>
#include <sstream>
#include <map>
#include<vector>

#define default_section "default";
using map_of_maps = std::map<std::string, std::map<std::string, std::string>>;
using insertion_vector = std::vector<std::string>;

class Configuration
{
    protected:
        insertion_vector _insertionMetaMap; 
        map_of_maps _internalRepresentation;
    public:
        std::string get(std::string section, std::string key);
        // TODO: implement
        // std::vector<std::string> getSection(std::string section); 
        bool set(std::string section, std::string key, std::string value);

};