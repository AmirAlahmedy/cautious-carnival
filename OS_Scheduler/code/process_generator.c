#include "headers.h"

#define MAXCHAR 1000
int readFile(char *filename, char lines[MAXCHAR][MAXCHAR]);
void clearResources(int);

struct process
{
    int id, arrival, runtime, priority;
};

int main(int argc, char *argv[])
{
    key_t msgqid;
    signal(SIGINT, clearResources);
    // TODO Initialization
    // 1. Read the input files.
    char lines[MAXCHAR][MAXCHAR], *filename = "processes.txt";
    int num_proc = readFile(filename, lines);
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
    // 3. Initiate and create the scheduler and clock processes.
    pid_t pid = fork();
    if (pid == 0)
    {
        system("./clk.out");
        puts("child");
    }
    else if (pid != -1)
    {
        puts("parent");

        if (fork() == 0)
            system("./scheduler.out");

        msgqid = msgget(12613, IPC_CREAT | 0644);
        if (msgqid == -1)
        {
            perror("Error in create");
            exit(-1);
        }
        printf("msgqid = %d\n", msgqid);

        // 4. Use this function after creating the clock process to initialize clock
        initClk();
        // To get time use this
        int x = getClk(), y, send_val;
        printf("current time is %d\n", x);
        struct process p_send;

        if (msgsnd(msgqid, &num_proc, sizeof(int), !IPC_NOWAIT) == -1)
            perror("Errror in sending number of processes");

        // TODO Generation Main Loop
        while (1)
        {
            // 5. Create a data structure for processes and provide it with its parameters.
            y = getClk();
            for (int i = 0; i < num_proc; i++)
                if ((y - x) == lines[i][1])
                {
                    p_send.id = (int)(lines[i][0]);
                    p_send.arrival = (int)(lines[i][1]);
                    p_send.runtime = (int)(lines[i][2]);
                    p_send.priority = (int)(lines[i][3]);
    
                    send_val = msgsnd(msgqid, &p_send, sizeof(struct process), !IPC_NOWAIT);
                    if (send_val == -1)
                        perror("Errror in sending processes");
                }
            // 6. Send the information to the scheduler at the appropriate time.
            // 7. Clear clock resources
        }
        msgctl(msgqid, IPC_RMID, (struct msqid_ds *)0);
        destroyClk(true);

    }
    else
    {
        perror("Error in fork");
        //exit(-1);
    }
}

void clearResources(int signum)
{
    //TODO Clears all resources in case of interruption
}

int readFile(char *filename, char lines[MAXCHAR][MAXCHAR])
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
    return l;
}
