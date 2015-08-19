#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "event.h"
#include "pthread.h"
#include "assert.h"
#define  BUF_BODY   "hello world\n"
 
void*
do_write( void * pArg )
{
    struct bufferevent *pBufEv = (struct bufferevent *)pArg;
 
    while(1)
    {
        bufferevent_write(pBufEv,BUF_BODY,strlen(BUF_BODY));
        sleep(1);
    }    
    return NULL;
}
 
void do_read( struct bufferevent * pBEv, void * pArg )
{
    struct evbuffer * pInput = bufferevent_get_input(pBEv);
    size_t nLen = evbuffer_get_length(pInput);
 
    if( nLen > 0 )
    {
        char * pData = (char *)malloc(nLen+1);
        evbuffer_remove(pInput, pData, nLen);
        pData[nLen] ='\0';
        printf("%s\n", pData);
        free(pData);
    }

    /* It make no effective */
    //bufferevent_enable(pBEv, EV_READ);
    return ; 
}
 
int main( void )
{
    struct event_base * pEventBase = NULL;
    struct bufferevent * aPair[2] = {NULL};
 
    pEventBase = event_base_new();
    if( NULL == pEventBase )
    {
        printf("event_base_new() 返回NULL值\n");
        return 0;
    }
 
    int nRet = bufferevent_pair_new(NULL, 0, aPair);
    if( 0 != nRet )
    {
        printf("bufferevent_pair_new()返回值为%d\n", nRet);
        event_base_free(pEventBase);
        return 0;
    }
 
    bufferevent_setcb(aPair[1], do_read, NULL, NULL, NULL);
    bufferevent_enable(aPair[1], EV_READ);
    bufferevent_enable(aPair[0], EV_WRITE);
 

    bufferevent_base_set (pEventBase, aPair[0]);

    pthread_t tid;
    pthread_create(&tid, NULL, do_write, aPair[0]);
    sleep(1);

    int cc = event_base_loop (pEventBase, EVLOOP_NO_EXIT_ON_EMPTY);
    printf ("cc == %d\n", cc);

    return 0;
}

