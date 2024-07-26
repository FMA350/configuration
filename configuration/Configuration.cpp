/*
 * Created on Mon Jul 22 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <Configuration.hpp>
#include <iostream>


std::pair<insertion_vector::iterator,insertion_vector::iterator> Configuration::_getSectionIterators(std::string section)
{
    insertion_vector::iterator b,e;
    auto ds =  default_section;
    if(section == ds)
    {
        b = _insertionMetaMap.begin();
    }
    else 
    {
        std::cout << "looking for " << section << std::endl;
        for(auto it = _insertionMetaMap.begin(); it != _insertionMetaMap.end(); ++it)
        {
            if(*it == "["+section+"]")
            {
                std::cout <<"FOUND:"<< *it << std::endl;
                b = it;
                break;
            }
        }
    }
    // Guard if b has not been set
    if(*b == "")
    {
        // TODO: maybe throw error?
        return {};
    }
    e = _insertionMetaMap.end();
    // Find next section or end
    // for(auto it = _insertionMetaMap.begin(); it != _insertionMetaMap.end(); it++)
    for(auto it = std::next(b); it != _insertionMetaMap.end(); it++)
    {
        std::cout << "it: " << *it << std::endl;
        if((*it)[0] == '[')
        {
            e = it;
            break;
            std::cout << "found"<< std::endl;
        }
        if(it == _insertionMetaMap.end())
        {
            std::cout << "bad"<< std::endl;

        }
    }
    
    std::cout << "B: " << *b << ", E: " << *e << "\n";

    return {b,e};
}


std::string Configuration::get(std::string section, std::string key)
{
    return _internalRepresentation[section][key];
}

std::list<std::string> Configuration::getKeysInSection(std::string section)
{
    // find the beginning of the section
    // Then go till next section or the end.
    // Remove every comment or empty line

    auto [s,e]= _getSectionIterators(section);
    auto sublist = std::list<std::string>(s,e);
    // Clean from comments and empty lines
    for(auto it = sublist.begin(); it != sublist.end(); )
    {
        if((*it)[0] == '#' || *it == "")
        {
            it = sublist.erase(it);
        }
        else 
        {
            ++it;
        }
    }
    return sublist;
}

bool Configuration::set(std::string section, std::string key, std::string value)
{
    bool existingSection = _internalRepresentation.find(section) != _internalRepresentation.end();
    bool existingValue =_internalRepresentation[section].find(key) != _internalRepresentation[section].end();
    if( existingSection && existingValue )
    {
        // exists and it's a simple update 
        _internalRepresentation[section][key] = value;
        return true;
    }
    else
    {
        // If new value create it & append it in the vector at a specific position
        if(existingSection)
        {
            _internalRepresentation[section][key] = value;
            auto [s, end] = _getSectionIterators(section);
            std::cout << " s =" << *s << " end " << *end << "\n";
            _insertionMetaMap.insert(end, key);
            
        }
        // If new section, create map, add value, then create section and value in the vector at the end.
        else
        {
            _internalRepresentation[section] = std::map<std::string, std::string>();
            _internalRepresentation[section][key] = value;
            std::cout << _internalRepresentation[section][key];
            _insertionMetaMap.push_back("["+section+"]");
            _insertionMetaMap.push_back(key);
        }
        return false; 
    }
}