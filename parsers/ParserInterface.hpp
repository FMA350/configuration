/*
 * Created on Sun Jul 21 2024
 *
 * Copyright (c) 2024 Moneta Software
 */
#pragma once
#include <Configuration.hpp>
// In charge of turning sstrings into data and data into sstrings
class ParserInterface
{
public:
    virtual std::pair<insertion_vector, map_of_maps> deserialize(const std::stringstream& ss) = 0;
    virtual std::stringstream serialize(const std::pair<insertion_vector, map_of_maps>& data) = 0;
};