#include <dlfcn.h>

int main(void)
{
    typedef void *(*fptr)();

    void *foo = dlopen("./libfoo.so", RTLD_NOW);
    void *bar = dlopen("./libbar.so", RTLD_NOW);
    void *gra = dlopen("./libgra.so", RTLD_NOW);

    fptr fooEntryPoint = (fptr)dlsym(foo, "myEntryPoint");
    (*fooEntryPoint)();

    fptr barEntryPoint = (fptr)dlsym(bar, "myEntryPoint");
    (*barEntryPoint)();

    fptr graEntryPoint = (fptr)dlsym(gra, "myEntryPoint");
    (*graEntryPoint)();

    dlclose(foo);
    dlclose(bar);
    dlclose(gra);
    return 0;
}
