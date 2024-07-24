#include "ConfigurationFile.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    auto p = std::string(argv[1]);
    auto c = ConfigurationFile(p);
    try
    {
        c.read();
        std::cout << "[section][key2] values is: " << c.get("section","key2") << "\n";
        c.set("section","key2", "512");
        std::cout << "[section][key2] values is now: " << c.get("section","key2") << "\n";
        c.write();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}