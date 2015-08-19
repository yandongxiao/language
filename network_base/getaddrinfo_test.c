#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{


    struct addrinfo *res = 0 ;
    struct addrinfo *org = 0 ;
    getaddrinfo("localhost", NULL ,NULL,&res);
    org = res;

    while(res)
    {
        printf("ai_flags -> %d\n", res->ai_flags) ;
        printf("ai_family -> %d\n", res->ai_family) ;
        printf("ai_socktype -> %d\n", res->ai_socktype) ;
        printf("ai_protocol -> %d\n", res->ai_protocol) ;
        printf("ai_addrlen -> %d\n", res->ai_addrlen) ;
        struct sockaddr_in* saddr = (struct sockaddr_in*)res->ai_addr;
        printf("ai_addr hostname ->  %s\n", inet_ntoa(saddr->sin_addr));

        res = res->ai_next;
    }

    freeaddrinfo(org);

    return 0 ;
}
