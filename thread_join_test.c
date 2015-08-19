#include <unistd.h>
#include <pthread.h> 
#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/***************************************************************************/
/* our macro for errors checking                                           */
/***************************************************************************/
#define COND_CHECK(func, cond, retv, errv) \
if ( (cond) ) \
{ \
   fprintf(stderr, "\n[CHECK FAILED at %s:%d]\n| %s(...)=%d (%s)\n\n",\
              __FILE__,__LINE__,func,retv,strerror(errv)); \
   exit(EXIT_FAILURE); \
}
 
#define ErrnoCheck(func,cond,retv)  COND_CHECK(func, cond, retv, errno)
#define PthreadCheck(func,rc) COND_CHECK(func,(rc!=0), rc, rc)


/*****************************************************************************/
/* thread- print point coordinate and terminate the process                  */
/*****************************************************************************/

struct point {
   int x;
   int y;
};

void*
thread(void* arg)
{
   struct point *p = (struct point*) arg;
   sleep (1);
   printf("(x,y) = (%d,%d)\n", p->x, p->y);
   exit(EXIT_SUCCESS);
}

/*****************************************************************************/
/* main- main thread                                                         */
/*****************************************************************************/
int
main()
{
   struct point p;
   pthread_t tid; 
   int rc; 
   
   p.x=0; p.y=42;
   rc = pthread_create(&tid, NULL, thread, &p);
   PthreadCheck("pthread_create", rc);
   pthread_detach (tid);
   // that's all for main thread
   pthread_exit(NULL);
}
