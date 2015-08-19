#include <unistd.h>
#include <stdio.h>

int main ()
{
    setgid(1000);
    setuid(1000);

    if(0==fork()) {
    	setsid();

	uid_t ruid, euid, suid;
	getresuid(&ruid, &euid, &suid);
	printf("ruid = %d\n", ruid);
	printf("euid = %d\n", euid);
	printf("suid = %d\n", suid);

	uid_t rgid, egid, sgid;
	getresgid (&rgid, &egid, &sgid);
	printf("rgid = %d\n", rgid);
	printf("egid = %d\n", egid);
	printf("sgid = %d\n", sgid);

        system ("ls /root");
	char *buff[3] = {"/bin/ls", "/root", NULL};
	execvp (buff[0],buff);
    }
    
    return 0;
}
