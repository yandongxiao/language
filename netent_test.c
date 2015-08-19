#include <stdio.h>
#include <netdb.h>

void
print_netent (struct netent *net)
{
    printf ("net_name = <%s>\n", net->n_name);

    int i;
    for (i=0; net->n_aliases[i]; i++) {
        printf ("net_alias[%d] = <%s>\n", i, net->n_aliases[i]);
    }

    if (net->n_addrtype == AF_INET)
        printf ("address_type = <%s>\n", "AF_INET");
    else if (net->n_addrtype == AF_INET6)
        printf ("address_type = <%s>\n", "AF_INET6");

    char buff[INET_ADDRSTRLEN];
//    inet_ntop (AF_INET, net->n_net, buff, INET_ADDRSTRLEN);
    printf ("network number = <%x>\n", net->n_net);
    printf ("\n\n");
}

int main ()
{
    struct netent *net;

    while ( (net=getnetent()) != NULL ) {
        print_netent (net);
    }
}
