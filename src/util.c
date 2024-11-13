#include "includes.h"

void Error(const char *function, const char *message)
{
    printf("ERROR: %s\n%s\n", function, message);
    exit(1);
}
