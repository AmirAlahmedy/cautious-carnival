#include "headers.h"
#include "Queue.h"

// void handler(int signum);
void sigalarm_handler(int signum)
{
    printf("alarm fired at t=%ld\n", time(NULL)); // write a message when called
}

int num = 0, pid[MAXCHAR];
struct process temp, discarded;
void roundRobin(struct Queue *Q, key_t msgqid, FILE *fp, int Quantum)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;
    alarm(1);
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);
    if (p_rec.state == ARRIVED)
    {
        num++;
        printf("num: %d\n", num);
        enQueue(Q, p_rec);
    }
    if (temp.id != 0)
        enQueue(Q, temp);

    if (!isEmpty(Q))
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: temp is %ld %d %d %d\n", getClk(), temp.id, temp.arrival, temp.runtime, temp.priority);

        printf("at %d: front is  %ld %d %d %d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.priority);

        if (Q->front->next != NULL)
            printf("at %d: front next is  %ld %d %d %d\n", getClk(), Q->front->next->key.id, Q->front->next->key.arrival, Q->front->next->key.runtime, Q->front->next->key.priority);

        printf("at %d: rear is %ld %d %d %d\n", getClk(), Q->rear->key.id, Q->rear->key.arrival, Q->rear->key.runtime, Q->rear->key.priority);

        pid[num] = fork();
        if (pid[num] == 0)
        {
            Q->front->key.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", Q->front->key.runtime);
            system(line);
            exit(7);
        }

        if (Q->front->key.state == ARRIVED)
        {
            Q->front->key.ST = getClk();
            Q->front->key.wait = Q->front->key.ST - Q->front->key.arrival;
            Q->front->key.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n", pid[num - 1], pid[num]);


        kill(Q->front->key.pid, SIGCONT);
        if (Q->front->key.state == STOPPED)
        {
            Q->front->key.state = RESUMED;
            Q->front->key.wait = getClk() - ((Q->front->key.runtime - Q->front->key.runtime) + Q->front->key.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
            fclose(fp);
        }

        if (Q->front->key.remain <= Quantum)
        {
            ch_pid = wait(&stat_loc);
            if (!(stat_loc & 0x00FF))
            {
                printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
                Q->front->key.remain = 0;
            }
        }
        else
        {
            alarm(Quantum);
            sleep(INT_MAX);
            kill(pid[num], SIGSTOP);
            Q->front->key.remain -= Quantum;
        }

        if (Q->front->key.state == RESUMED || Q->front->key.state == STARTED)
        {
            if (Q->front->key.remain == 0)
            {
                Q->front->key.state = FINISHED;
                int TA = getClk() - Q->front->key.ST;
                Q->front->key.wait = TA - Q->front->key.runtime;
                float WTA = 0;
                if (Q->front->key.runtime != 0)
                    WTA = TA / Q->front->key.runtime;
                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait, TA, WTA);
                fclose(fp);
            }
            else
            {
                Q->front->key.state = STOPPED;
                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
                fclose(fp);
            }
        }

        if (Q->front->key.remain == 0)
        {
            discarded = (deQueue(Q))->key;
            temp.id = 0;
        }
        else
        {
            temp = Q->front->key;
            discarded = (deQueue(Q))->key; 
        }
    }
}

int i = -1, prev_finish, max_i;
float WTA_HPF = 0.0;
bool first = true, ProcRunning = false;
void HPF(key_t msgqid, FILE *fp)
{
    int pid, msgqid2, msgqid3;

    struct process p_rec = {.id = OO, /*.arrival = 0, .runtime = 0, .priority =  0*/};
    struct longProcess p_long, p_longarr[MAXCHAR];
    int maxPrior = OO;

    msgqid2 = msgget(12614, IPC_CREAT | 0644);
    msgqid3 = msgget(12615, IPC_CREAT | 0644);

    int isProcessRec = OO;

    if (msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, IPC_NOWAIT) == -1)
        ;
    // perror("Scheduler(HPF): Error in receiving processes");

    isProcessRec = p_rec.id;
    // printf("pid rec: %d\n", isProcessRec);
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
        if (/* (getClk() == prev_finish && getClk() >= p_longarr[max_i].arrival) || (getClk() == p_longarr[max_i].arrival && p_longarr[max_i].arrival >= prev_finish) && */ !ProcRunning)
        {
            started_time = getClk();
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", started_time, p_longarr[max_i].id, p_longarr[max_i].state, p_longarr[max_i].arrival, p_longarr[max_i].runtime, p_longarr[max_i].remain, p_longarr[max_i].wait);
            fclose(fp);
            ProcRunning = true;
            printf("process %ld sent at %d\n", p_longarr[max_i].id, getClk());
            if ((msgsnd(msgqid2, &p_longarr[max_i], sizeof(p_longarr[max_i]), !IPC_NOWAIT)) == -1)
                perror("Scheduler(HPF): Error in sending runtime to the process");
        }
    }

    struct longProcess finished_process;
    if (i != -1 && ProcRunning)
    {
        // printf("%ld %d %d %d\n", p_longarr[max_i].id, p_longarr[max_i].arrival, p_longarr[max_i].runtime, p_longarr[max_i].priority);
        // printf("%ld %d %d %d\n", p_longarr[1].id, p_longarr[1].arrival, p_longarr[1].runtime, p_longarr[1].priority);

        switch (fork())
        {
        case 0:
            system("./process.out");
            break;
        case -1:
            // perror("Scheduler(HPF): Error in fork");
            break;
        default:

            // if (/* ((getClk() == prev_finish && getClk() >= p_longarr[max_i].arrival) || (getClk() == p_longarr[max_i].arrival && p_longarr[max_i].arrival >= prev_finish) &&  */ !ProcRunning /* ) */)
            // {
            //     ProcRunning = true;
            //     printf("process %ld sent at %d\n", p_longarr[max_i].id, getClk());
            //     if ((msgsnd(msgqid2, &p_longarr[max_i], sizeof(p_longarr[max_i]), !IPC_NOWAIT)) == -1)
            //         perror("Scheduler(HPF): Error in sending runtime to the process");
            // }

            if ((msgrcv(msgqid3, &finished_process, sizeof(finished_process), 0, IPC_NOWAIT)) == -1)
                ; // perror("Scheduler(HPF): Error in receiving finished process");

            if (finished_process.id != 0 /* && ProcRunning */)
            {
                int TA = finished_process.finished - finished_process.arrival;
                WTA_HPF = (WTA_HPF * (i) + TA) / (i + 1);
                printf("Finished process %ld, its remain is %d\n", finished_process.id, finished_process.remain);
                finished_process.state = "finished";

                printf("arrIndx %d\n", finished_process.arrIndx);
                printf("max_i %d\n", max_i);
                p_longarr[max_i].priority = OO;

                // printf(fp, finished_process.state);

                printf("#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", finished_process.finished, finished_process.id, finished_process.state, finished_process.arrival, finished_process.runtime, finished_process.remain, finished_process.wait, TA, WTA_HPF);
                printf("\n(Scheduler) process %ld finished at %d, and its index is %d\n", finished_process.id, finished_process.finished, finished_process.arrIndx);

                prev_finish = finished_process.finished;
                ProcRunning = false;

                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\t%s\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", finished_process.finished, finished_process.id, finished_process.state, finished_process.arrival, finished_process.runtime, finished_process.remain, finished_process.wait, TA, WTA_HPF);
                fclose(fp);

                remove_from_array(p_longarr, finished_process.arrIndx, i + 1);
                i--;
            }

            break;
        }
    }
    // msgctl(msgqid2, IPC_RMID, (struct msqid_ds *)0);
    // msgctl(msgqid3, IPC_RMID, (struct msqid_ds *)0);
}

void SRTN(key_t msgqid)
{
    struct process p_rec, proc_arr[MAXCHAR];
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);

    if (fork() == 0)
        system("process.out");
    while (1)
        sleep(INT_MAX);
}

int main(int argc, char *argv[])
{
    initClk();

    // signal(SIGINT, handler);
    signal(SIGALRM, sigalarm_handler);

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

    struct Queue *Q = createQueue();
    switch (d.scheduling_algo)
    {
    case 1:
        /* Round Robin */
        while (1)
            roundRobin(Q, msgqid, fp, d.quantum);
        break;

    case 2:
        /* SRTN */
        while (1)
            SRTN(msgqid);
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