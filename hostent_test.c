#include <netdb.h>
#include <stdio.h>

void
print_hostent (struct hostent *host)
{
    printf ("host_name = <%s>\n", host->h_name);


    int i;
    for (i=0; host->h_addr_list[i]; i++) {
        char buff[INET_ADDRSTRLEN];
        inet_ntop (AF_INET, host->h_addr_list[i], buff, INET_ADDRSTRLEN);
        printf ("host_addr[%d] = <%s>\n", i, buff);
    }

    for (i=0; host->h_aliases[i]; i++) {
        printf ("host_alis[%d] = <%s>\n", i, host->h_aliases[i]);
    }
    
    if (host->h_addrtype == AF_INET)
        printf ("address_type = <%s>\n", "AF_INET");
    else if (host->h_addrtype == AF_INET6)
        printf ("address_type = <%s>\n", "AF_INET6");

    printf ("\n\n");
}

int
main (void)
{
    struct hostent *host;

    while ( (host=gethostent()) != NULL ) {
        print_hostent (host);
    }

    endhostent ();


    return 0;
}

