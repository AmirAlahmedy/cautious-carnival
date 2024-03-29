#include "headers.h"
#include <string.h>

int readFile(char *filename, int lines[][COLS]);
void clearResources(int);


int msgqid, scheduler_pid, shmid;

int main(int argc, char *argv[])
{
    signal(SIGINT, clearResources);
    // signal(SIGUSR1, sigusr1_handler);
    // TODO Initialization
    // 1. Read the input files.
    int lines[MAXCHAR][COLS];
    char *filename = "processes.txt";
    int num_proc = readFile(filename, lines);
    // printf("memo %d\n", lines[0][4]);
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
    int quantum, choice;
    printf("\nChoose the scheduling algorithm:  \n");
    printf("1.Round Robin \n");
    printf("2.SRTN \n");
    printf("3.Nonpreemptive HPF \n");
    printf("4.Quit \n\n");
    printf("Enter your choice : ");

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("\nEnter the quantum: ");
        scanf("%d", &quantum);
        break;
    case 4:
        exit(1);
        break;
    default:
        break;
    }
    // 3. Initiate and create the scheduler and clock processes.
    int pid = fork();
    if (pid == 0)
    {
        //execl("/home/amir/Desktop/Fall 2019/Operatimg Systems/project (phases1 & 2)/project/OS-Phase1_2/OS_Scheduler/code/clk.out", "./clk.out", NULL);
        system("./clk.out");
        exit(0);
    }
    else if (pid != -1)
    {
        // 4. Use this function after creating the clock process to initialize clock
        initClk();

        msgqid = msgget(12613, IPC_CREAT | 0644);
        if (msgqid == -1)
        {
            perror("Process Generator: Error in create");
            exit(-1);
        }

        shmid = shmget(5, sizeof(int), IPC_CREAT | 0644);
        int *allSent = (int*)shmat(shmid, (void *)0, 0);

        if (fork() == 0)
        {
            scheduler_pid = getpid();
            system("./scheduler.out");
            exit(0);
        }

        // To get time use this
        int x = getClk(), y, send_val;
        printf("Process Generator: current time is %d\n", x);

        struct process p_send;

        struct details d;
        d.mtype = 7;
        d.num_proc = num_proc;
        d.scheduling_algo = choice;
        d.quantum = quantum;

        if ((msgsnd(msgqid, &d, sizeof(d), !IPC_NOWAIT)) == -1)
            perror("Process Generator: Errror in sending details");

        bool sent[num_proc], and[num_proc];
        for (int i = 0; i < num_proc; i++)
            and[i] = sent[i] = 0;

        // TODO Generation Main Loop
        *allSent = 0;
        while (1)
        {
            // 5. Create a data structure for processes and provide it with its parameters.
            y = getClk();
            for (int i = 0; i < num_proc; i++)
            {
                if (y == lines[i][1] && !sent[i])
                {
                    and[i] = sent[i] = 1;
                    p_send.id = lines[i][0];
                    p_send.arrival = lines[i][1];
                    p_send.runtime = p_send.remain = lines[i][2];
                    p_send.priority = lines[i][3];
                    p_send.memsize = lines[i][4];
                    p_send.index = -1;
                    p_send.state = ARRIVED;

                    send_val = msgsnd(msgqid, &p_send, sizeof(p_send), !IPC_NOWAIT);
                    kill(scheduler_pid, SIGCONT);
                    if (send_val == -1)
                        perror("Process Generator: Errror in sending processes");
                }
            }
            if(sent[num_proc - 1] == 1)
            {
                // sleep(5);
                *allSent = 1;
                shmdt(allSent);
                sleep(INT_MAX);
            }
            // 6. Send the information to the scheduler at the appropriate time.
            // 7. Clear clock resources
        }
        puts("allSent");
        // msgctl(msgqid, IPC_RMID, (struct msqid_ds *)0);
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
    // TODO: Clears all resources in case of interruption
    kill(scheduler_pid, SIGINT);
    msgctl(msgqid, IPC_RMID, (struct msqid_ds *)0);
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
    destroyClk(true);
    kill(getpid(), SIGKILL);
}

int readFile(char *filename, int lines[][COLS])
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
    return l;
}
