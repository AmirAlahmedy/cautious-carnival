#include "headers.h"

/* Modify this file as needed*/
int remainingtime;
struct longProcess rec_proc;

int main(int agrc, char *argv[])
{
    union Semun semun;

    int sem = semget(110, 1, 0666 | IPC_CREAT);
    semun.val = 1;
    if (semctl(sem, 0, SETVAL, semun) == -1)
        fprintf(stderr, "Error in semctl");

    down(sem);
    initClk();

    //TODO it needs to get the remaining time from somewhere: from the scheduler
    //remainingtime = ??;
    int msgqid2 = msgget(12614, IPC_CREAT | 0644);
    int msgqid3 = msgget(12615, IPC_CREAT | 0644);
    if ((msgrcv(msgqid2, &rec_proc, sizeof(rec_proc), 0, !IPC_NOWAIT)) == -1)
        perror("Process: Error in receiving runtime");

    printf("process %ld received at %d\n", rec_proc.id, getClk());
    printf("Current Process: %ld %d %d %d\n", rec_proc.id, rec_proc.arrival, rec_proc.runtime, rec_proc.priority);
    remainingtime = rec_proc.remain;
    int start = getClk();
    while (remainingtime > 0)
    {
        // printf("\n%d\n", getClk());
        remainingtime = rec_proc.runtime - (getClk() - start);
        // printf("\nprocess no. %d remaining time = %d", rec_proc.id, remainingtime);
    }
    rec_proc.remain = remainingtime;
    rec_proc.finished = getClk();

    printf("process no. %ld finished time = %d\n", rec_proc.id, rec_proc.finished);

    if ((msgsnd(msgqid3, &(rec_proc), sizeof(rec_proc), !IPC_NOWAIT)) == -1)
        perror("Process: Errror in sending finished process to the scheduler");

    destroyClk(false);
    // msgctl(msgqid2, IPC_RMID, (struct msqid_ds *)0);
    // msgctl(msgqid3, IPC_RMID, (struct msqid_ds *)0);
    puts("process terminating");
    up(sem);

    return 0;
}
