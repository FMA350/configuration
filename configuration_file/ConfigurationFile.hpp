/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */

#include <string>
#include <sstream>
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
        ConfigurationFile(std::string p) : _path(p){};
        void read();
        void write();
};