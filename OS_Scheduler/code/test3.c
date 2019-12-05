#include <stdio.h>

#define LEN 256
int main()
{
    FILE *fp;
    
    /* open the file for writing*/
    fp = fopen("scheduler.log", "w");

    /* write 10 lines of text into the file stream*/
    fprintf(fp, "test\n");

    /* close the file*/
    fclose(fp);
    return 0;
}