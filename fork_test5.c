#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

int main ()
{
    struct tms tmsstart;
    struct tms tmsend;

    int clktck = sysconf (_SC_CLK_TCK);
    printf ("%d clocks per second\n", clktck);

    /* unsigned long format. */
    clock_t begin = times (&tmsstart);
    system("date;ls;find . -name \".h\"");
    clock_t end = times (&tmsend);
//    wait(NULL);
    
    printf ("process has run %lu clocks\n", end-begin);
    printf ("parrt sys %lu clocks\n", tmsend.tms_stime - tmsstart.tms_stime);
    printf ("parrt usr %lu clocks\n", tmsend.tms_utime - tmsstart.tms_utime);
    printf ("child sys %lu clocks\n", tmsend.tms_cstime - tmsstart.tms_cstime);
    printf ("child usr %lu clocks\n", tmsend.tms_cutime - tmsstart.tms_cutime);    
    
    
    return 0;
}
