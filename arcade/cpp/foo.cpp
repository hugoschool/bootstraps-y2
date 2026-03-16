#include <stdio.h>

#define LIB_NAME "foo"

__attribute__((constructor)) void constructor(void)
{
    printf("[lib%s] Loading %s library...\n", LIB_NAME, LIB_NAME);
}

__attribute__((destructor)) void destructor(void)
{
    printf("[lib%s] %s closing...\n", LIB_NAME, LIB_NAME);
}

extern "C" void myEntryPoint(void)
{
    printf("[lib%s] Entry point for %s!\n", LIB_NAME, LIB_NAME);
}
