/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once

#include <ParserInterface.hpp>

class DefaultParser : public ParserInterface
{
private:
    bool isComment(const std::string&);
    bool isSection(const std::string&);
    bool isKeyValuePair(const std::string&);
public:
    virtual std::pair<insertion_vector, map_of_maps> deserialize(const std::stringstream&) override;
    virtual std::stringstream serialize(const std::pair<insertion_vector, map_of_maps>&) override;

};
