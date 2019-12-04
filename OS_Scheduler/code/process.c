#include "headers.h"

/* Modify this file as needed*/
int remainingtime;
struct longProcess rec_proc;

int main(int agrc, char *argv[])
{
    initClk();

    //TODO it needs to get the remaining time from somewhere: from the scheduler
    //remainingtime = ??;
    int msgqid = msgget(12614, IPC_CREAT | 0644);
    if (msgrcv(msgqid, &rec_proc, sizeof(struct longProcess), rec_proc.id, !IPC_NOWAIT) == -1)
        perror("Process: Error in receiving runtime");

    remainingtime = rec_proc.remain;
    while (remainingtime > 0)
    {
        remainingtime--;
        printf("\nprocess no. %d remaining time = %d", rec_proc.id, remainingtime);
    }
    if (msgsnd(msgqid, &rec_proc.arrIndx, sizeof(int), !IPC_NOWAIT) == -1)
        perror("Process: Errror in sending finished process arrIndex to scheduler");

    destroyClk(false);

    return 0;
}
