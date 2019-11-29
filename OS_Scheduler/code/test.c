#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 1000
void readFile(char *filename, char lines[MAXCHAR][MAXCHAR]);
int main(int argc, char const *argv[])
{
    // system("bash read.sh processes.txt");
    char lines[MAXCHAR][MAXCHAR], *filename = "processes.txt";
    readFile(filename, lines);

    for (int j = 0; j < 3; j++)
        printf("%s\n", lines[j]);

    return 0;
}

void readFile(char *filename, char lines[MAXCHAR][MAXCHAR])
{
    FILE *fp;
    char str[MAXCHAR];
    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("Could not open file %s", filename);

    int l = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        if (str[0] == '#')
            continue;

        for (int j = 0, k = 0; str[j] != '\n'; j++)
        {
            if (str[j] == '\t')
                continue;
            lines[l][k] = str[j];
            k++;
        }
        l++;
    }
    fclose(fp);
    return;
}
