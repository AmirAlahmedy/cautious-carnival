#include "headers.h"

struct process
{
    int id, arrival, runtime, priority;
};

int main(int argc, char *argv[])
{
    initClk();

    key_t msgqid;
    msgqid = msgget(12613, IPC_CREAT | 0644);
    if (msgqid == -1)
    {
        perror("Error in create");
        exit(-1);
    }

    int rec_val, num_proc;
    if (msgrcv(msgqid, &num_proc, sizeof(int), 0, !IPC_NOWAIT) == -1)
        perror("Error in receiving number of processes");

    struct process p_send[num_proc];
    int i = 0;
    while (1)
    {
        rec_val = msgrcv(msgqid, &p_send, sizeof(struct process), 0, !IPC_NOWAIT);
        if (rec_val == -1)
            perror("Error in receiving processes");
    }

    //TODO implement the scheduler :)
    //upon termination release the clock resources

    destroyClk(true);
}
/* 
    atoi
    how to implement our code while in loop it blocks
    exit
    sending processes
    sending number of proceses or making the size static
 */