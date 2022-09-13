#include "server/server_tcp_create.h"

/**
 *
 * fonction server_tcp_create port:number
 *
 * crée/bind/listen sur une socket
 * retourne le descripteur de la socket ( -1 si erreur )
 * 
 */
int server_tcp_create(uint16_t port){
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);

    if(socket_fd < 0){
        goto error;
    }
    logger("server-tcp", "server_tcp_create (%d)", port);

    struct sockaddr_in socket_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    logger("server-tcp", "socket_addr");

    if(bind(socket_fd, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) < 0){
        goto error;
    }
    logger("server-tcp", "bind");

    if(listen(socket_fd, 0) < 0){
        goto error;
    }
    logger("server-tcp", "listen");
    
    return socket_fd;

    error:
        close(socket_fd);
        return -1;
}