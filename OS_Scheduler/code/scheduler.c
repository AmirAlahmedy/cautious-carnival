#include "headers.h"
#include "Queue.h"



void roundRobin(int Quantum, struct Queue *Q)
{
    // TODO: Complete
    struct longProcess p;
    p.remain = p.t->runtime;

    while (!isEmpty(Q))
    {
        p = (deQueue(Q))->key;
        p.wait = getClk() - p.t->arrival;
        p.remain = p.t->runtime - Quantum;

        // TODO: Double check the conditions
        p.state = p.state == NULL ? "started"
                 : (p.state == "stopped") && (p.remain > 0) ? "resumed"
                 : (p.state == "started" || p.state == "resumed") && (p.remain > 0) ? "stopped"
                 : "finished";

        if(p.state != "finished")        
            enQueue(Q, p);
    }
}

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

    struct process p_rec;
    struct longProcess p_long;
    struct Queue *Q = createQueue();
    int choice = 0, quantum = 1;

    while (1)
    {
        if (msgrcv(msgqid, &p_rec, sizeof(struct process), 0, !IPC_NOWAIT) == -1)
            perror("Error in receiving processes");

        
        /* push the received process into the process queue */
        p_long.t = &p_rec;
        enQueue(Q, p_long);

        switch (choice)
        {
        case 0:
            /* Round Robin */
            roundRobin(quantum, Q);
            break;

        case 1:
            /* SRTN */
            break;

        case 2:
            /* non preemptive HPF */
            break;

        default:
            break;
        }
    }

    //TODO implement the scheduler :)
    //upon termination release the clock resources

    destroyClk(true);
}
/* // TODO: 
    atoi - done 
    how to implement our code while in loop it blocks - done
    exit
    sending processes
    sending number of proceses or making the size static
    **Amir** send a struct containing the details(the algorithm and its parameters) or pass them as argv
 */