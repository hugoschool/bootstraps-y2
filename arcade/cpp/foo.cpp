#include "foo.hpp"
#include <iostream>

Foo::Foo::Foo() : _name("foo")
{
    std::cout << "[lib" << _name << "] Loading " << _name << " library..." << std::endl;
}

Foo::Foo::~Foo()
{
    std::cout << "[lib" << _name << "] " << _name << " closing..." << std::endl;
}

void Foo::init()
{
    std::cout << "[lib" << _name << "] was initialized..." << std::endl;
}

void Foo::stop()
{
    std::cout << "[lib" << _name << "] was stopped..." << std::endl;
}

const std::string &Foo::getName() const
{
    return _name;
}

extern "C" {
    IDisplayModule *entrypoint()
    {
        return new Foo;
    }
}
