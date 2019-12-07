#include "headers.h"
#include "Queue.h"

// void handler(int signum);

void roundRobin(int Quantum)
{
}

int i = -1, prev_finish, max_i;
float WTA_HPF = 0.0;
bool first = true;
void HPF(key_t msgqid, FILE *fp)
{
    int pid, msgqid2, msgqid3;

    struct process p_rec = {.id = OO, /*.arrival = 0, .runtime = 0, .priority =  0*/};
    struct longProcess p_long, p_longarr[MAXCHAR];
    int maxPrior = OO;

    msgqid2 = msgget(12614, IPC_CREAT | 0644);
    msgqid3 = msgget(12615, IPC_CREAT | 0644);

    int isProcessRec = OO;

    if (msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT) == -1)
        perror("Scheduler(HPF): Error in receiving processes");

    isProcessRec = p_rec.id;
    printf("pid rec: %d\n", isProcessRec);
    if (first)
    {
        first = false;
        // printf("\n(%d)\n", isProcessRec);
        prev_finish = p_rec.arrival;
        // printf("first finish is %d\n", prev_finish);
    }

    if (isProcessRec != OO)
    {
        printf("%ld %d %d %d\n", p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        p_long.id = p_rec.id;
        p_long.arrival = p_rec.arrival;
        p_long.priority = p_rec.priority;
        p_long.remain = p_long.runtime = p_rec.runtime;
        p_long.state = "arrived";
        p_long.wait = 0;

        i++; // i += countarr
        p_longarr[i] = p_long;
        max_i = i;
        for (int j = 1; j <= i; j++)
        {
            p_longarr[j].arrIndx = j;
            if ((maxPrior > p_longarr[j].priority) /* && (p_longarr[j].remain == p_longarr[j].runtime) */)
            {
                maxPrior = p_longarr[j].priority;
                max_i = j;
            }
        }
        p_longarr[max_i].state = "started";
        p_longarr[max_i].wait = getClk() - p_longarr[max_i].arrival;

        int started_time;
        if ((getClk() == prev_finish && getClk() >= p_longarr[max_i].arrival))
            started_time = prev_finish;
        else if ((getClk() == p_longarr[max_i].arrival && p_longarr[max_i].arrival >= prev_finish))
            started_time = getClk();

        fp = fopen("scheduler.log", "a");
        fprintf(fp, "#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", started_time, p_longarr[max_i].id, p_longarr[max_i].state, p_longarr[max_i].arrival, p_longarr[max_i].runtime, p_longarr[max_i].remain, p_longarr[max_i].wait);
        fclose(fp);
    }

    struct longProcess finished_process;
    if (i != -1)
    {
        printf("%ld %d %d %d\n", p_longarr[max_i].id, p_longarr[max_i].arrival, p_longarr[max_i].runtime, p_longarr[max_i].priority);
        printf("%ld %d %d %d\n", p_longarr[1].id, p_longarr[1].arrival, p_longarr[1].runtime, p_longarr[1].priority);
        switch (fork())
        {
        case 0:
            system("./process.out");
            break;
        case -1:
            perror("Scheduler(HPF): Error in fork");
            break;
        default:
            if ((getClk() == prev_finish && getClk() >= p_longarr[max_i].arrival) || (getClk() == p_longarr[max_i].arrival && p_longarr[max_i].arrival >= prev_finish))
            {
                printf("process %ld sent at %d\n", p_longarr[max_i].id, getClk());
                if ((msgsnd(msgqid2, &p_longarr[max_i], sizeof(p_longarr[max_i]), !IPC_NOWAIT)) == -1)
                    perror("Scheduler(HPF): Error in sending runtime to the process");
            }

            if ((msgrcv(msgqid3, &finished_process, sizeof(finished_process), 0, !IPC_NOWAIT)) == -1)
                perror("Scheduler(HPF): Error in receiving finished process");

            int TA = finished_process.finished - finished_process.arrival;
            WTA_HPF = (WTA_HPF * (i) + TA) / (i + 1);
            printf("Finished process %ld, its remain is %d\n", finished_process.id, finished_process.remain);
            finished_process.state = "finished";
            prev_finish = finished_process.finished;

            printf("arrIndx %d\n", finished_process.arrIndx);
            printf("max_i %d\n", max_i);
            p_longarr[max_i].priority = OO;

            // printf(fp, finished_process.state);

            printf("#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", finished_process.finished, finished_process.id, finished_process.state, finished_process.arrival, finished_process.runtime, finished_process.remain, finished_process.wait, TA, WTA_HPF);
            printf("\n(Scheduler) process %ld finished at %d, and its index is %d\n", finished_process.id, finished_process.finished, finished_process.arrIndx);

            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", finished_process.finished, finished_process.id, finished_process.state, finished_process.arrival, finished_process.runtime, finished_process.remain, finished_process.wait, TA, WTA_HPF);
            fclose(fp);

            remove_from_array(p_longarr, finished_process.arrIndx, i + 1);
            i--;
            break;
        }
    }
    // msgctl(msgqid2, IPC_RMID, (struct msqid_ds *)0);
    // msgctl(msgqid3, IPC_RMID, (struct msqid_ds *)0);
}

void SRTN()
{
}

int main(int argc, char *argv[])
{
    initClk();

    // signal(SIGINT, handler);

    key_t msgqid;
    msgqid = msgget(12613, IPC_CREAT | 0644);
    if (msgqid == -1)
    {
        perror("Scheduler: Error in create");
        // exit(-1);
    }

    struct details d;

    if ((msgrcv(msgqid, &d, sizeof(d), 7, !IPC_NOWAIT)) == -1)
        perror("Scheduler: Error in receiving details");
    // printf("%d%d%d", d.num_proc, d.quantum, d.scheduling_algo);

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
        /* non preemptive HPF */
        while (1)
            HPF(msgqid, fp);
        break;

    default:
        break;
    }

    //TODO implement the scheduler :)
    //upon termination release the clock resources
}

// void handler(int signum)
// {
//     destroyClk(true);
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