/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#include <DefaultParser.hpp>
#include <sstream>
#include <iostream>

bool DefaultParser::isComment(const std::string& s)
{
    return s[0] == '#';
}

bool DefaultParser::isSection(const std::string& s)
{
    return s[0] == '[';
}

bool DefaultParser::isKeyValuePair(const std::string& s)
{
    return s.find(':') != s.npos; 
}

std::pair<insertion_vector, map_of_maps> DefaultParser::deserialize(const std::stringstream& ss)
{
    map_of_maps map_data;
    insertion_vector insertion_data;

    std::string current;
    std::string section = default_section;
    
    // Create default section
    map_data[section] = std::map<std::string, std::string>();
    
    auto copy = std::stringstream(ss.str());
    while( std::getline(copy,current))
    {
        // Line could be a comment, a section, or a key:value pair.
        if(isComment(current))
        {
            insertion_data.push_back(current);
            continue;
        }
        if(isSection(current))
        {
            // create new section
            insertion_data.push_back(current);
            section = current.substr(1, current.size()-2);
            map_data[section] = std::map<std::string, std::string>();
            continue;
        }
        if(isKeyValuePair(current))
        {
            // key value pair
            auto div = current.find(':');
            auto key = current.substr(0,div);
            auto val = current.substr(div+1, current.size());
            map_data[section][key] = val;
            insertion_data.push_back(key);
            continue;
        }
        throw std::runtime_error("bad string in configuration: " + current);
    }

    return make_pair(insertion_data,map_data);
}

std::stringstream DefaultParser::serialize(const std::pair<insertion_vector, map_of_maps>& data)
{
    std::stringstream ss;
    std::string section = default_section;
    for(auto& s : data.first)
    {
        if(isComment(s))
        {
            ss << s << std::endl;
            continue;
        }
        if(isSection(s))
        {
            ss << s << std::endl;
            section = s.substr(1,s.size()-2);
            continue;
        }
        // is a key value pair
        auto m = data.second;

        ss << s+":"+m[section][s] << std::endl;
        continue;
    }
    return ss;
}