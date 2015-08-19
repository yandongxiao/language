

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void
sig_user (int signo) {
    sigflag = 1;
}

void
TELL_WAIT (void)
{
    signal (SIGUSR1, sig_user);    
    signal (SIGUSR2, sig_user);

    sigemptyset (&newmask);
    sigemptyset (&zeromask);
    
    sigaddset (&newmask, SIGUSR1);
    sigaddset (&newmask, SIGUSR2);

    sigprocmask (SIG_BLOCK, &newmask, &oldmask);
}

void
TELL_PARRENT (pid_t pid) 
{
    kill (pid, SIGUSR2);
}

void
TELL_CHILD (pid_t pid)
{
    kill (pid, SIGUSR1);
}

void
WAIT_PARRENT(pid_t pid)
{
    while (sigflag==0)
        sigsuspend (&zeromask);
    sigflag = 0;

    sigprocmask (SIG_SETMASK, &oldmask, NULL);
}

void
WAIT_CHILD (pid_t pid)
{
    WAIT_PARRENT (pid);
}
