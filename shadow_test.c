#include <shadow.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h> /* for uid_t */

/*
 * 1. set user id should be set.
 * 2. on mounted fs, chmod 04777 dose not work. and all files and dirs are 0777.
 */
int
main (void)
{
    struct spwd * sp = getspnam ("jail");
    uid_t id = geteuid ();
    if (id != 0) {
        assert (sp == NULL);
    }
    else {
        assert (sp != NULL);
        printf ("encrypt password is : %s\n", sp->sp_pwdp);
       
    }
    return 0;
}
