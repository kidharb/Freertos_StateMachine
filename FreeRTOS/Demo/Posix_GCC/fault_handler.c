#include "Fault.h"
#include <stdio.h>
#include <stdlib.h>

// Simple fault handler implementation for C
void FaultHandler(const char* file, unsigned short line)
{
    printf("FAULT: Assertion failed at %s:%d\n", file, line);
    // In a real embedded system, you might want to reset or take other action
    // For this demo, we'll just print and continue
    // abort(); // Uncomment this line if you want the program to terminate on assertion
}