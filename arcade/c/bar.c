#include <stdio.h>

#define LIB_NAME "bar"

__attribute__((constructor)) void constructor(void)
{
    printf("[lib%s] Loading %s library...\n", LIB_NAME, LIB_NAME);
}

__attribute__((destructor)) void destructor(void)
{
    printf("[lib%s] Closing %s...\n", LIB_NAME, LIB_NAME);
}

void myEntryPoint(void)
{
    printf("[lib%s] Entry point for %s!\n", LIB_NAME, LIB_NAME);
}
