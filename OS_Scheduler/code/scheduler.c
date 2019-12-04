#include "headers.h"
#include "Queue.h"

void roundRobin(int Quantum)
{
    // // TODO: Complete
    // struct longProcess p;
    // p.remain = p.t->runtime;

    // while (!isEmpty(Q))
    // {
    //     p = (deQueue(Q))->key;
    //     p.wait = getClk() - p.t->arrival;
    //     p.remain = p.t->runtime - Quantum;

    //     // TODO: Double check the conditions
    //     p.state = p.state == NULL ? "started"
    //                               : (p.state == "stopped") && (p.remain > 0) ? "resumed"
    //                                                                          : (p.state == "started" || p.state == "resumed") && (p.remain > 0) ? "stopped"
    //                                                                                                                                             : "finished";

    //     if (p.state != "finished")
    //         enQueue(Q, p);
    // }
}

int i = -1;
void HPF(key_t msgqid)
{
    int s;
    scanf("%d", &s);
    int pid, msgqid2;
    struct process p_rec;
    struct longProcess p_long;
    struct longProcess p_longarr[MAXCHAR];
    
    msgqid2 = msgget(12614, IPC_CREAT | 0644);

    if (msgrcv(msgqid, &p_rec, sizeof(struct process), 0, !IPC_NOWAIT) == -1)
        perror("Scheduler(HPF): Error in receiving processes");

    /* push the received process into the process queue */
    p_long.id = &p_rec.id;
    p_long.arrival = &p_rec.arrival;
    p_long.priority = &p_rec.priority;
    p_long.remain = p_long.runtime = &p_rec.runtime;

    i++;
    p_longarr[i] = p_long;
    int max_prior = OO, max_i;
    for (int j = 0; j <= i; j++)
    {
        if(max_prior > p_longarr[j].priority)
        {
            max_prior = p_longarr[j].priority;
            max_i = j;
            p_longarr[j].arrIndx = max_i;
        }
    }

    int finished_index;
    if (i != -1)
    {
        switch (fork())
        {
        case 0:
            system("./process.out");
            break;
        case 1:
            if (msgsnd(msgqid2, &p_longarr, sizeof(struct longProcess), !IPC_NOWAIT) == -1)
                perror("Scheduler(HPF): Error in sending runtimes to processes");
            if (msgrcv(msgqid2, &finished_index, sizeof(int), 0, !IPC_NOWAIT) == -1)
                perror("Scheduler(HPF): Error in receiving remaining time from the process");
            else
                remove_from_array(p_longarr, finished_index, i + 1);
            break;
        case -1:
            perror("Scheduler(HPF): Error in fork");
            break;
        default:
            break;
        }
    }
}

void SRTN()
{
}
void handler(int pid, struct process p_rec, key_t msgqid);


int main(int argc, char *argv[])
{
    initClk();

    signal(SIGUSR1, handler);

    key_t msgqid;
    msgqid = msgget(12613, IPC_CREAT | 0644);
    if (msgqid == -1)
    {
        perror("Scheduler: Error in create");
        exit(-1);
    }

    struct details d;
    // sleep(5);
    if (msgrcv(msgqid, &d, sizeof(d), 0, !IPC_NOWAIT) == -1)
        perror("Scheduler: Error in receiving details");
    printf("%d%d%d", d.num_proc, d.quantum, d.scheduling_algo);
    switch (d.scheduling_algo)
    {
    case 1:
        /* Round Robin */
        while (1)
            roundRobin(d.quantum);
        break;

    case 2:
        /* SRTN */
        while (1)
            SRTN();
        break;

    case 3:
        /* non preemptive HPF */
        while (1)
            HPF(msgqid);
        break;

    default:
        break;
    }

    //TODO implement the scheduler :)
    //upon termination release the clock resources

    destroyClk(true);
}

void handler(int pid, struct process p_rec, key_t msgqid)
{
    if (msgrcv(msgqid, &p_rec, sizeof(struct process), 0, !IPC_NOWAIT) == -1)
        perror("Error in receiving processes");
}

/* // TODO: 
    atoi - done 
    how to implement our code while in loop it blocks - done
    exit
    sending processes
    sending number of proceses or making the size static
    **Amir** send a struct containing the details(the algorithm and its parameters) or pass them as argv
    Error: sh: 1: ./process.c: Permission denied
 */