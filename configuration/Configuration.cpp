/*
 * Created on Mon Jul 22 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <Configuration.hpp>

std::string Configuration::get(std::string section, std::string key)
{
    return _internalRepresentation[section][key];
}

bool Configuration::set(std::string section, std::string key, std::string value)
{
    if( _internalRepresentation.find(section) != _internalRepresentation.end() && _internalRepresentation[section].find(key) != _internalRepresentation[section].end())
    {
        // exists and it's a simple update
        _internalRepresentation[section][key] = value;
        return true;
    }
    else
    {
        // TODO: add creation of new sections or keys and update _internalRepresentation and _insertionVector
        return false; 
    }
}