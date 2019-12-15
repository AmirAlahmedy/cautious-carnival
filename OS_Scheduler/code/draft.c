// SJF
void HPF()
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
//Working correctly but log is wrong
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
