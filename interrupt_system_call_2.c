#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
void ding(int sig)
{
    printf("Ding!\n");
}
 
struct msgst
{
    long int msg_type;
    char buf[1];
};
 
int main()
{
    int nMsgID = -1;
 
    struct sigaction action;
    action.sa_handler = ding;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    
    /* version 1: do not set SA_RESTART attr */
    /* version 2: do not set SA_RESTART attr */
    action.sa_flags |= SA_RESTART;
    sigaction(SIGALRM, &action, NULL);
    alarm(3);
    printf("waiting for alarm to go off\n");
 
    // ÐÂ½¨ÏûÏ¢¶ÓÁÐ
    nMsgID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if( nMsgID < 0 )
    {
        perror("msgget fail" );
        return;
    }
    printf("msgget success.\n");
 
    // ×èÈû µÈ´ýÏûÏ¢¶ÓÁÐ
    //
    // msgrcv»áÒòÎª½ø³ÌÊÕµ½ÁËÐÅºÅ¶øÖÐ¶Ï¡£·µ»Ø-1£¬errno±»ÉèÖÃÎªEINTR¡£
    // ¼´Ê¹ÔÚ²åÈëÐÅºÅÊ±ÉèÖÃÁËSA_RESTART£¬Ò²ÎÞÐ§¡£man msgrcv¾ÍÓÐËµÃ÷¡
    //
    struct msgst msg_st;
    if( -1 == msgrcv( nMsgID, (void*)&msg_st, 1, 0, 0 ) )
    {
        perror("msgrcv fail");
    }
 
    printf("done\n");
 
    exit(0);
}

