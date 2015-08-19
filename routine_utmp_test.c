#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <utmp.h>

int main (int argc, char *argv[]) {
   struct itimerval delay;
   struct utmp *utmpstruct;
   int numuser = 0;

   setutent();
   while ((utmpstruct = getutent())) {
   	if ((utmpstruct->ut_type == USER_PROCESS) &&
        	(utmpstruct->ut_name[0] != '\0')){
                numuser++;
		printf("ut_user : %s\n", utmpstruct->ut_user);
		printf("ut_name : %s\n", utmpstruct->ut_name);
        }
   }
   endutent();
   printf("found %d users\n", numuser);
   return 0;
}
