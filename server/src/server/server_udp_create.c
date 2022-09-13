#include "server/server_udp_create.h"

int multicast_udp_create(char *host, char *service, struct sockaddr **ip)
{
    /*int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        return -1;
    }
    
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(9999)
    };
    addr.sin_addr.s_addr = inet_addr("239.0.0.1");
    socklen_t addrlen = sizeof(addr);*/
    struct addrinfo *f, *r;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int k = getaddrinfo(host, service, &hints, &f);
    if (k < 0)
    {
        return -1;
    }

    int s;
    for (r = f; r != NULL; r = r->ai_next)
    {
        s = socket(PF_INET, SOCK_DGRAM, 0);
        if (s < 0)
        {
            continue;
        }

        if (connect(s, r->ai_addr, r->ai_addrlen) == 0)
        {
            *ip = r->ai_addr;
            return s;
        }

        close(s);
    }

    return -1;
}