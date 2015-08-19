#include <pwd.h>    /* for struct passwd */
#include <assert.h>
#include <stdio.h>

void
printf_pwd (struct passwd *pwd)
{
    printf ("username : %s\n", pwd->pw_name);
    printf ("password : %s\n", pwd->pw_passwd);
    printf ("userid   : %u\n", pwd->pw_uid);
    printf ("usergid  : %u\n", pwd->pw_gid);
    printf ("realname : %s\n", pwd->pw_gecos);
    printf ("dir name : %s\n", pwd->pw_dir);    
    printf ("shell    : %s\n\n", pwd->pw_shell);

}

int
main (void)
{
    struct passwd *pwd;
    pwd = getpwnam ("jail");
    printf_pwd (pwd);

    pwd = getpwnam ("test");
    printf_pwd (pwd);

    pwd = getpwuid(1000);
    printf_pwd (pwd);

    pwd = getpwuid (2000);
    assert (NULL == pwd);

    setpwent();
    while((pwd = getpwent ()) != NULL) {
        printf_pwd (pwd);
    }
    endpwent();
    return 0;

}
