#include "foo.hpp"
#include "bar.hpp"
#include "gra.hpp"
#include "DLLoader.hpp"
#include <dlfcn.h>
#include <iostream>

int main(void)
{
    // UGLY but idc
    DLLoader<Foo> fooLoader("./libfoo.so");
    DLLoader<Bar> barLoader("./libbar.so");
    DLLoader<Gra> graLoader("./libgra.so");

    Foo *foo = fooLoader.getInstance();
    foo->init();
    std::cout << "Name: " << foo->getName() << std::endl;
    foo->stop();

    Bar *bar = barLoader.getInstance();
    bar->init();
    std::cout << "Name: " << bar->getName() << std::endl;
    bar->stop();

    Gra *gra = graLoader.getInstance();
    gra->init();
    std::cout << "Name: " << gra->getName() << std::endl;
    gra->stop();

    delete foo;
    delete bar;
    delete gra;
    return 0;
}
