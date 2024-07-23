/*
/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <string>
#include <ConfigurationFile.hpp>

class Configuration : ConfigurationFile
{
    private:
        
    public:
        std::string get(std::string parameterName);
        bool set(std::string parameterName, std::string value);

};