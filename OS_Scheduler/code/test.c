#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 4
#define MAXCHAR 1000
void readFile(char *filename, int *lines);
int getNumOfProc(char *filename);

int main(int argc, char const *argv[])
{
    char *filename = "processes.txt";
    int rows = getNumOfProc(filename);
    //int lines[MAXCHAR][COLS];

    int *lines = (int *)malloc(rows * COLS * sizeof(int));
    // printf("\n");
    printf("%d", *(lines + 0 * COLS + 0));

    // scanf("%d", &rows);
    readFile(filename, lines);
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < COLS; j++)
            printf("%d ", *(lines + i * COLS + j));
        printf("\n");

    }
    free(lines);

    return 0;
}

int getNumOfProc(char *filename)
{
    FILE *fp;
    char str[MAXCHAR];

    int l = 0;
    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("Could not open file %s", filename);

    while (fgets(str, MAXCHAR, fp) != NULL)
        if (str[0] != '#')
            l++;

    fclose(fp);
    return l;
}

void readFile(char *filename, int *lines)
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

            lines[l * COLS + k] = atoi(num);
            //  *(lines + COLS * l + k) = atoi(num);
              k++;
        }

        l++;
    }
    fclose(fp);
    return;
}
