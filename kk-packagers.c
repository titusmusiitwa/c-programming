#include <stdio.h>

/**
 * main - program entry point
 * Return: Always 0 (success)
 */

int main(void)
{

    return (0);
}

void fileWrite(FILE *ofp, char *name)
{
    char *bpr;
    size_t buffer_size = 1032;
    char buffer[buffer_size];

    if (!ofp)
        ofp = fopen(name, "a");
}