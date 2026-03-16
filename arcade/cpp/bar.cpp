#include "bar.hpp"
#include <iostream>

Bar::Bar::Bar() : _name("bar")
{
    std::cout << "[lib" << _name << "] Loading " << _name << " library..." << std::endl;
}

Bar::Bar::~Bar()
{
    std::cout << "[lib" << _name << "] " << _name << " closing..." << std::endl;
}

void Bar::init()
{
    std::cout << "[lib" << _name << "] was initialized..." << std::endl;
}

void Bar::stop()
{
    std::cout << "[lib" << _name << "] was stopped..." << std::endl;
}

const std::string &Bar::getName() const
{
    return _name;
}

extern "C" {
    IDisplayModule *entrypoint()
    {
        return new Bar;
    }
}
