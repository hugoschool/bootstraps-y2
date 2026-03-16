#include "gra.hpp"
#include <iostream>

Gra::Gra::Gra() : _name("gra")
{
    std::cout << "[lib" << _name << "] Loading " << _name << " library..." << std::endl;
}

Gra::Gra::~Gra()
{
    std::cout << "[lib" << _name << "] " << _name << " closing..." << std::endl;
}

void Gra::init()
{
    std::cout << "[lib" << _name << "] was initialized..." << std::endl;
}

void Gra::stop()
{
    std::cout << "[lib" << _name << "] was stopped..." << std::endl;
}

const std::string &Gra::getName() const
{
    return _name;
}

extern "C" {
    IDisplayModule *entrypoint()
    {
        return new Gra;
    }
}
