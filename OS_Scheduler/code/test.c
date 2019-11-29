#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
void readFile(char *filename, int lines[MAXCHAR][MAXCHAR]);
int main(int argc, char const *argv[])
{
    // system("bash read.sh processes.txt");
    int lines[MAXCHAR][MAXCHAR];
    char *filename = "processes.txt";
    readFile(filename, lines);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%d ", lines[i][j]);

        printf("\n");
    }

    return 0;
}

void readFile(char *filename, int lines[MAXCHAR][MAXCHAR])
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
            char num[] = "";
            if (str[j] == '\t')
                continue;

            while (isdigit(str[j]))
                strncat(num, &str[j++], 1);
           
            lines[l][k++] = atoi(num);
            
        }

        l++;
    }
    fclose(fp);
    return;
}
