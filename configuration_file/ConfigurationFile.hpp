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

// in charge of loading and saving a file

class ConfigurationFile
{
    private:
        std::string _path;
        std::shared_ptr<ParserInterface> _parser;

        insertion_vector _insertionMetaMap;
        map_of_maps _internalRepresentation;

    public:
        ConfigurationFile(std::string);
        void read();
        void write();
};