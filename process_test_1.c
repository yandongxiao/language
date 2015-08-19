#include <unistd.h>
#include <stdio.h>
#include <pwd.h>

int main ()
{
  /* 
     * create accout tttt, but you can not login by tttt to CTL+AL&+7.
     * you can verify it on CTRL+ALT+1.
     * login by tttt.
     */

    struct passwd *pw = getpwuid (getuid());
    /* print jail .*/
    printf("the process name is :%s\n", pw->pw_name);

    /* print tttt, this is what you want. */
    /* do not need free. */
    printf("the process name is :%s\n", getlogin());

    /* If this process has close STDIN_FILENO, 
        * getlogin return NULL. we call it no terminal connected. */
    close (STDIN_FILENO);
    /* you can comment them */
//    close (STDOUT_FILENO);
//    close (STDERR_FILENO);

    /* */
    if (getlogin() == NULL)
        return 1;
    return 0;
}
