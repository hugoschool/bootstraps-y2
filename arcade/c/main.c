#include <dlfcn.h>

#define LIBRARY_AMOUNT 3

typedef void *(*fptr)();

int main(void)
{
    char *libNames[LIBRARY_AMOUNT] = {
        "./libfoo.so",
        "./libbar.so",
        "./libgra.so",
    };
    void *handles[LIBRARY_AMOUNT] = {0};

    for (size_t i = 0; i < LIBRARY_AMOUNT; i++)
        handles[i] = dlopen(libNames[i], RTLD_NOW);
    for (size_t i = 0; i < LIBRARY_AMOUNT; i++) {
        fptr entrypoint = (fptr)dlsym(handles[i], "myEntryPoint");
        (*entrypoint)();
    }
    for (size_t i = 0; i < LIBRARY_AMOUNT; i++)
        dlclose(handles[i]);
    return 0;
}
