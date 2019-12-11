#include "headers.h"

/* Modify this file as needed*/
int remainingtime;

int main(int agrc, char *argv[])
{
    initClk();

    // printf("%d\n", clock() / CLOCKS_PER_SEC);
    //TODO it needs to get the remaining time from somewhere
    char *p;
    int run = strtol(argv[1], &p, 10);
    while (run != clock() / CLOCKS_PER_SEC)
    {
        // printf("%d %d\n", run, clock()/CLOCKS_PER_SEC);
    };
    // puts("finished");

    destroyClk(false);

    return 0;
}
