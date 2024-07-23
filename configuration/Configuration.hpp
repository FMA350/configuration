/*
/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once
#include <string>
#include <ConfigurationFile.hpp>

class Configuration : ConfigurationFile
{
    private:
        
    public:
        std::string get(std::string section, std::string parameterName);
        // TODO: implement
        // std::vector<std::string> getSection(std::string section); 
        bool set(std::string section, std::string parameterName, std::string value);

};