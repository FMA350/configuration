/*
/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once

#include <string>
#include <map>
#include<list>

#define default_section "default";
using map_of_maps = std::map<std::string, std::map<std::string, std::string>>;
using insertion_vector = std::list<std::string>;

class Configuration
{
    private:
        std::pair<insertion_vector::iterator,insertion_vector::iterator> _getSectionIterators(std::string section);

    protected:
        insertion_vector _insertionMetaMap; 
        map_of_maps _internalRepresentation;
    public:
        // Get value of a variable
        std::string get(std::string section, std::string key);
        // get list of keys in a section by insertion
        insertion_vector getKeysInSection(std::string section);
        bool set(std::string section, std::string key, std::string value);

};