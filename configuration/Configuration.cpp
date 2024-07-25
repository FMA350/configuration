/*
 * Created on Mon Jul 22 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <Configuration.hpp>


std::pair<insertion_vector::iterator,insertion_vector::iterator> Configuration::_getSectionIterators(std::string section)
{
    insertion_vector::iterator b,e;
    for(auto it = _insertionMetaMap.begin(); it != _insertionMetaMap.end(); ++it)
    // for(auto&v: _insertionMetaMap)
    {
        if(*it == "["+section+"]")
        {
            b = it;
            break;
        }
    }
    // Guard if b has not been set
    if(*b == "")
    {
        return {};
    }
    
    // Find next section or end
    for(auto it = b; it != _insertionMetaMap.end(); ++it)
    {
        if((*it)[0] == '[')
        {
            e = it;
            break;
        }
    }

    if(*e == "")
    {
        e = _insertionMetaMap.end();
    }
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

    auto p = _getSectionIterators(section);
    auto sublist = std::list<std::string>(p.first,p.second);
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
            
        }
        // If new section, create map, add value, then create section and value in the vector at the end.
        else
        {
            _internalRepresentation[section] = std::map<std::string, std::string>();
            _insertionMetaMap.push_back("["+section+"]");
            _insertionMetaMap.push_back("key");
        }
        return false; 
    }
}