#ifndef SERVER_UDP_CREATE_H
#define SERVER_UDP_CREATE_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int multicast_udp_create(char *host, char *service, struct sockaddr **ip);

#endif // SERVER_UDP_CREATE_H
