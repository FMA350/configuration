/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

#include <ParserInterface.hpp>
#include <Configuration.hpp>


// in charge of loading and saving a file
class ConfigurationFile : public Configuration
{
    protected:
        std::string _path;
        std::shared_ptr<ParserInterface> _parser;

    public:
        ConfigurationFile(std::string);
        void read();
        void write();
};