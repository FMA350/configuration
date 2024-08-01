/*
 * Created on Mon Jul 22 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <Configuration.hpp>


std::pair<insertion_vector::iterator,insertion_vector::iterator> Configuration::_getSectionIterators(std::string section)
{
    insertion_vector::iterator b,e;

    bool beginninggFound = false;
    bool endFound = false;
    if(section == default_section)
    {
        b = _insertionMetaMap.begin();
        beginninggFound = true;
    }

    for(int i = 0; i < _insertionMetaMap.size(); i++)
    {
        if(beginninggFound)
        {
            if( _insertionMetaMap[i] != *b && _insertionMetaMap[i][0] == '[')
            {
                // found the end
                e = _insertionMetaMap.begin() + i;
                endFound = true;
                break;
            }
        }
        else
        {
            if( _insertionMetaMap[i] == "["+section+"]" && _insertionMetaMap[i][0] == '[')
            {
                // found the beginning
                beginninggFound = true;
                b = _insertionMetaMap.begin() + i;
            }

        }
    }
    if(beginninggFound && !endFound)
    {
        // end must be last element of the vector
        e = _insertionMetaMap.end() - 1;
    }
    return {b,e};
}

std::string Configuration::get(std::string section, std::string key)
{
    return _internalRepresentation[section][key];
}

insertion_vector Configuration::getKeysInSection(std::string section)
{
    // find the beginning of the section
    // Then go till next section or the end.
    // Remove every comment or empty line

    auto [s,e]= _getSectionIterators(section);
    auto sublist = insertion_vector(s,e);
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
            _insertionMetaMap.insert(end, key);

        }
        // If new section, create map, add value, then create section and value in the vector at the end.
        else
        {
            _internalRepresentation[section] = std::map<std::string, std::string>();
            _internalRepresentation[section][key] = value;
            _insertionMetaMap.push_back("["+section+"]");
            _insertionMetaMap.push_back(key);
        }
        return false;
    }
}
