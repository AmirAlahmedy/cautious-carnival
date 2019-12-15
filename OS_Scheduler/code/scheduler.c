#include "headers.h"
#include "Queue.h"
#include "priority_queue.h"
int *allSent;
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
            Q->front->key.wait = getClk() - ((Q->front->key.runtime - Q->front->key.remain) + Q->front->key.arrival);
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
/* used in HPF and SRTN */
int len;
Node *PQ;
bool noProcRunning = 1;
void HPF(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;
    if (!(*allSent))
        msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);
    if (p_rec.state == ARRIVED)
    {
        num++;
        push(&PQ, p_rec, p_rec.priority);
        printf("peek is %ld\n", peek(&PQ).id);
        len++;
        printf("num: %d, len: %d\n", num, len);
    }

    if (len)
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);

        if (PQ->data.state == ARRIVED && noProcRunning)
        {
            noProcRunning = 0;
            pid[num] = fork();
            if (pid[num] == 0)
            {
                PQ->data.pid = pid[num];
                char line[20];
                sprintf(line, "./process.out %d", PQ->data.runtime);
                system(line);
                exit(7);
            }

            PQ->data.ST = getClk();
            PQ->data.wait = PQ->data.ST - PQ->data.arrival;
            PQ->data.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n", pid[num - 1], pid[num]);

        int option = *allSent ? (1) : (1 | WNOHANG);
        printf("allsent is %d\n", *allSent);
        ch_pid = waitpid(pid[num], &stat_loc, option);
        printf("Ch_pid is %d\n", ch_pid);
        if (ch_pid != 0 && !(stat_loc & 0x00FF))
        {
            noProcRunning = 1;
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            PQ->data.remain = 0;

            PQ->data.state = FINISHED;
            int TA = getClk() - PQ->data.ST;
            PQ->data.wait = TA - PQ->data.runtime;
            float WTA = 0;
            if (PQ->data.runtime != 0)
                WTA = TA / PQ->data.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait, TA, WTA);
            fclose(fp);

            printf("at %d: process popped is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
            pop(&PQ);
            len--;
        }
    }
}
void SJF(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;

    // if (!(*allSent))
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);

    if (p_rec.state == ARRIVED)
    {
        num++;
        push(&PQ, p_rec, p_rec.remain);
        printf("peek is %ld\n", peek(&PQ).id);
        len++;
        printf("num: %d, len: %d\n", num, len);
    }

    if (len)
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);

        if (PQ->next->data.state == RESUMED || PQ->next->data.state == STARTED)
        {
            kill(pid[num - 1], SIGSTOP); // stop the running process
            if (PQ->next->data.state = STARTED)
                PQ->next->data.remain = PQ->next->data.runtime - (getClk() - PQ->next->data.ST);
            // else if(PQ->data.state = RESUMED)
            //     PQ->data.remain =
            PQ->next->data.state = STOPPED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.remain, PQ->next->data.wait);
            fclose(fp);
        }

        pid[num] = fork();
        if (pid[num] == 0)
        {
            PQ->data.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", PQ->data.runtime);
            system(line);
            exit(7);
        }

        if (PQ->data.state == ARRIVED)
        {
            PQ->data.ST = getClk();
            PQ->data.wait = PQ->data.ST - PQ->data.arrival;
            PQ->data.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n\n", pid[num - 1], pid[num]);

        if (PQ->data.state == STOPPED)
        {
            kill(PQ->data.pid, SIGCONT);
            PQ->data.state = RESUMED;
            PQ->data.wait = getClk() - ((PQ->data.runtime - PQ->data.remain) + PQ->data.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        // alarm(5);
        ch_pid = waitpid(PQ->data.pid, &stat_loc, 0);
        if (ch_pid != 0 && !(stat_loc & 0x00FF))
        {
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            PQ->data.remain = 0;

            PQ->data.state = FINISHED;
            int TA = getClk() - PQ->data.ST;
            PQ->data.wait = TA - PQ->data.runtime;
            float WTA = 0;
            if (PQ->data.runtime != 0)
                WTA = TA / PQ->data.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait, TA, WTA);
            fclose(fp);
            printf("at %d: process popped is %ld %d %d %d\n\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
            pop(&PQ);
            len--;
        }
    }
}

/**
 * The type sig_atomic_t is used in C99 to guarantee
 * that a variable can be accessed/modified in an atomic way
 * in the case an interruption (reception of a signal for example) happens.
 */
static volatile sig_atomic_t done_waiting = 0;

static void sigusr_handler(int signum)
{
    if (signum == SIGCONT)
    {
     
        printf("Signal caught, a process is being receeived\n");
        done_waiting = 1;
    }
    else if (signum == SIGUSR2)
    {
        printf("Signal caught, Child terminated\n");
        done_waiting = 1;
    }
}



void my_pause()
{
    /**
   *  In ISO C, the signal system call is used
   *  to call a specific handler when a specified
   *  signal is received by the current process.
   *  In POSIX.1, it is encouraged to use the sigaction APIs.
   **/
    signal(SIGCONT, sigusr_handler);
    signal(SIGUSR2, sigusr_handler);
    done_waiting = 0;
    while (!done_waiting)
    {
        sleep(INT_MAX);
    }
}

void SRTN(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;

    // if (!(*allSent))
    // int rcvop = *allSent ? !IPC_NOWAIT : IPC_NOWAIT;
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);

    if (p_rec.state == ARRIVED)
    {
        num++;
        push(&PQ, p_rec, p_rec.remain);
        printf("peek is %ld\n", peek(&PQ).id);
        len++;
        printf("num: %d, len: %d\n", num, len);
    }

    if (len)
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
        printf("at %d: PQ front next is %ld %d %d %d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.priority);

        if (PQ->next->data.state == RESUMED || PQ->next->data.state == STARTED)
        {
            kill(pid[num - 1], SIGSTOP); // stop the running process
            if (PQ->next->data.state = STARTED)
                PQ->next->data.remain = PQ->next->data.runtime - (getClk() - PQ->next->data.ST);
            // else if(PQ->data.state = RESUMED)
            //     PQ->data.remain =
            PQ->next->data.state = STOPPED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.remain, PQ->next->data.wait);
            fclose(fp);
        }

        pid[num] = fork();
        if (pid[num] == 0)
        {
            PQ->data.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", PQ->data.runtime);
            system(line);
            kill(getppid(), SIGUSR2);
            exit(7);
        }

        if (PQ->data.state == ARRIVED)
        {
            PQ->data.ST = getClk();
            PQ->data.wait = PQ->data.ST - PQ->data.arrival;
            PQ->data.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n\n", pid[num - 1], pid[num]);

        if (PQ->data.state == STOPPED)
        {
            kill(PQ->data.pid, SIGCONT);
            PQ->data.state = RESUMED;
            PQ->data.wait = getClk() - ((PQ->data.runtime - PQ->data.remain) + PQ->data.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        // int options = *allSent ? 0 : 1 | WNOHANG;
        my_pause();
        ch_pid = waitpid(PQ->data.pid, &stat_loc, 0 | WNOHANG);
        if (ch_pid != 0 && !(stat_loc & 0x00FF))
        {
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            PQ->data.remain = 0;

            PQ->data.state = FINISHED;
            int TA = getClk() - PQ->data.ST;
            PQ->data.wait = TA - PQ->data.runtime;
            float WTA = 0;
            if (PQ->data.runtime != 0)
                WTA = TA / PQ->data.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait, TA, WTA);
            fclose(fp);
            printf("at %d: process popped is %ld %d %d %d\n\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
            pop(&PQ);
            len--;
        }
    }
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
    struct process dummy = {.state = UNDEFINED}; // used in RR
    PQ = NewNode(dummy, INT_MAX);                // used in SRTN
    int shmid = shmget(5, sizeof(int), IPC_CREAT | 0644);
    allSent = (int *)shmat(shmid, (void *)0, 0);

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
            SRTN(msgqid, fp);
        break;

    case 3:
        /* non preemptive HPF */
        while (1)
            HPF(msgqid, fp);
        break;

    default:
        break;
    }

    shmdt(allSent);
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