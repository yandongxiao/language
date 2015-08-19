#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main ()
{
    /* offen used by recv */
    zmq_msg_t msg;
    zmq_msg_init (&msg);
    size_t len =  zmq_msg_size (&msg);
    printf ("len==%u\n", len);  /* len==0 */
    zmq_msg_close (&msg);

    /* offen use by sned */
    zmq_msg_init_size (&msg, 10);
    len =  zmq_msg_size (&msg);
    printf ("len==%u\n", len);  /* len==0 */
    zmq_msg_close (&msg);

    return 0;
}
