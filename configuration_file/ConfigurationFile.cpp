#include <fstream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <ConfigurationFile.hpp>
#include <DefaultParser.hpp>

ConfigurationFile::ConfigurationFile(std::string path): _path(path)
{
    _parser = std::make_shared<DefaultParser>();
};

void ConfigurationFile::read()
{
    // open file
    std::stringstream data;
    std::ifstream f (_path);
    if(f.is_open())
    {
        std::string line;
        while ( std::getline (f,line) )
        {
            data << line << std::endl;
        }
        f.close();
    }
    else
    {
        throw std::runtime_error(std::string("File at " + _path + " could not be opened for reading"));
    }

    if(!_parser)
    {
        throw std::runtime_error(std::string("No _parser for " + _path));
    }
    
    std::tie(_insertionMetaMap,_internalRepresentation) = _parser->deserialize(data);

}

void ConfigurationFile::write()
{

    if(!_parser)
    {
        throw std::runtime_error(std::string("No _parser for " + _path));
    }

    auto data = _parser->serialize(std::make_pair(_insertionMetaMap,_internalRepresentation));

    std::ofstream f(_path);
    if(f.is_open())
    {
        std::string l;
        while( std::getline(data,l))
        {
            f << l;
            if(data.peek() != EOF)
            {
                f << std::endl;
            }
        }
        f.close();
    }
    else
    {
        throw std::runtime_error(std::string("File at " + _path + " could not be opened for writing"));
    }
}

