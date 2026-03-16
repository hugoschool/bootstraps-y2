#include <stdio.h>

#define LIB_NAME "gra"

__attribute__((constructor)) void constructor(void)
{
    printf("[lib%s] Loading %s library...\n", LIB_NAME, LIB_NAME);
}

__attribute__((destructor)) void destructor(void)
{
    printf("[lib%s] %s's getting out...\n", LIB_NAME, "Gra");
}

void myEntryPoint(void)
{
    printf("[lib%s] Another entry point!\n", LIB_NAME);
}
