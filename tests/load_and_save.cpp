#include "ConfigurationFile.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    auto p = std::string(argv[1]);
    auto c = ConfigurationFile(p);
    try
    {
        c.read();
        c.write();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}