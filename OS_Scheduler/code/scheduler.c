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

int i = -1, WTA_HPF = 0;
void HPF(key_t msgqid, FILE *fp)
{
    int pid, msgqid2;
    
    struct process p_rec = {.id = OO, .arrival = 0, .runtime = 0, .priority = 0};
    struct longProcess p_long;
    struct longProcess p_longarr[MAXCHAR];

    msgqid2 = msgget(12614, IPC_CREAT | 0644);

    int isProcessRec = OO;
    
    if (msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT) == -1)
        perror("Scheduler(HPF): Error in receiving processes");

    isProcessRec = p_rec.id;
    
    if (isProcessRec != OO)
    {

        fp = fopen("scheduler.log", "a");

        /* push the received process into the process queue */
        p_long.id = p_rec.id;
        p_long.arrival = p_rec.arrival;
        p_long.priority = p_rec.priority;
        p_long.remain = p_long.runtime = p_rec.runtime;
        p_long.state = "arrived";
        p_long.wait = 0;

        i++; // TODO: only if a process was received
        p_longarr[i] = p_long;
        int niceness = OO, max_i;
        for (int j = 0; j <= i; j++)
        {
            if (niceness > p_longarr[j].priority)
            {
                niceness = p_longarr[j].priority;
                max_i = j;
                p_longarr[j].arrIndx = max_i;
            }
        }
        p_longarr[max_i].state = "started";
        p_longarr[max_i].wait = getClk() - p_longarr[max_i].arrival;

        // puts("check stack");
        fprintf(fp, "#At time\t%d\tprocess\t%d\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), p_longarr[max_i].id, p_longarr[max_i].state, p_longarr[max_i].arrival, p_longarr[max_i].runtime, p_longarr[max_i].remain, p_longarr[max_i].wait);
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
            break;
        case -1:
            perror("Scheduler(HPF): Error in fork");
            break;
        default:
            if ((msgsnd(msgqid2, &p_longarr, sizeof(p_longarr), !IPC_NOWAIT)) == -1)
                perror("Scheduler(HPF): Error in sending runtimes to processes");
            if ((msgrcv(msgqid2, &finished_index, sizeof(finished_index), 0, !IPC_NOWAIT)) == -1)
                perror("Scheduler(HPF): Error in receiving remaining time from the process");
            // I hope it waits until it receives the finished index
            int finished_time = getClk();
            int TA = finished_time - p_longarr[finished_index].arrival;
            WTA_HPF = (WTA_HPF * (i - 1) + TA) / i;
            printf("process %d finished\n", p_longarr[finished_index].id);
            fprintf(fp, "#At time\t%d\tprocess\t%d\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%d\n", finished_time, p_longarr[finished_index].id, p_longarr[finished_index].state, p_longarr[finished_index].runtime, p_longarr[finished_index].remain, p_longarr[finished_index].wait, TA, WTA_HPF);
            i = remove_from_array(p_longarr, finished_index, i + 1);
            break;
        }
    }
    fclose(fp);
}

void SRTN()
{
}
// void handler(int pid, struct process p_rec, key_t msgqid);

int main(int argc, char *argv[])
{
    initClk();

    // signal(SIGUSR1, handler);

    key_t msgqid;
    msgqid = msgget(12613, IPC_CREAT | 0644);
    if (msgqid == -1)
    {
        perror("Scheduler: Error in create");
        exit(-1);
    }

    struct details d;

    if ((msgrcv(msgqid, &d, sizeof(d), 7, !IPC_NOWAIT)) == -1)
        perror("Scheduler: Error in receiving details");
    printf("%d%d%d", d.num_proc, d.quantum, d.scheduling_algo);

    FILE *fp;
    fp = fopen("scheduler.log", "w");
    fprintf(fp, "#At time\tx\tprocess\ty\tstate\tarr\tw\ttotal\tz\tremain\ty\twait\tk\n");
    fclose(fp);

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
        // puts("arrived at hpf");
        /* non preemptive HPF */
        while (1)
            HPF(msgqid, fp);
        break;

    default:
        break;
    }

    //TODO implement the scheduler :)
    //upon termination release the clock resources

    destroyClk(true);
}

// void handler(int pid, struct process p_rec, key_t msgqid)
// {
//     if (msgrcv(msgqid, &p_rec, sizeof(struct process), 0, !IPC_NOWAIT) == -1)
//         perror("Error in receiving processes");
// }

/* // TODO: 
    atoi - done 
    how to implement our code while in loop it blocks - done
    exit
    sending processes
    sending number of proceses or making the size static
    **Amir** send a struct containing the details(the algorithm and its parameters) or pass them as argv
    Error: sh: 1: ./process.c: Permission denied
 */