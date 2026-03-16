#include "foo.hpp"
#include "bar.hpp"
#include "gra.hpp"
#include <dlfcn.h>
#include <iostream>

int main(void)
{
    // UGLY but idc
    void *fooHandle = dlopen("./libfoo.so", RTLD_LAZY);
    void *barHandle = dlopen("./libbar.so", RTLD_LAZY);
    void *graHandle = dlopen("./libgra.so", RTLD_LAZY);

    Foo *(*fooFct)() = (Foo *(*)())dlsym(fooHandle, "entrypoint");
    Foo *foo = (*fooFct)();
    foo->init();
    std::cout << "Name: " << foo->getName() << std::endl;
    foo->stop();

    Bar *(*barFct)() = (Bar *(*)())dlsym(barHandle, "entrypoint");
    Bar *bar = (*barFct)();
    bar->init();
    std::cout << "Name: " << bar->getName() << std::endl;
    bar->stop();

    Gra *(*graFct)() = (Gra *(*)())dlsym(graHandle, "entrypoint");
    Gra *gra = (*graFct)();
    gra->init();
    std::cout << "Name: " << gra->getName() << std::endl;
    gra->stop();

    delete foo;
    delete bar;
    delete gra;

    dlclose(fooHandle);
    dlclose(barHandle);
    dlclose(graHandle);
    return 0;
}
