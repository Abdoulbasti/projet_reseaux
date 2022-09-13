#include "server/server_tcp_accept.h"

/**
 *
 * fonction server_tcp_accept socket_d:number client_accepted_handler:* message_handler:*
 *
 * accepter des clients sur une socket 
 * retourne 0 ( -1 si erreur )
 * 
 */
int server_tcp_accept(int socket_d,
                      void *(*client_accepted_handler)(void *arg),
                      int (*message_handler)(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message))
{
    logger("server-tcp", "server_tcp_accept");
    while(1){
        // création de l'argument du thread
        server_accept_t *args = (server_accept_t *)malloc(sizeof(server_accept_t));
        socklen_t len = sizeof(args->address);
        // acceptation des client
        args->socket = accept(socket_d, (struct sockaddr *)&args->address, &len);
        // définition de la fonction qui gère les message reçu
        args->message_handler = message_handler;
        logger("server-tcp", "client_accepted");
        if (args->socket < 0)
        {
            goto error;
        }

        pthread_t th;
        logger("server-tcp", "pthread_create");
        // création du thread
        int th_r = pthread_create(&th, NULL, client_accepted_handler, (void *)args);

        if (th_r < 0)
        {
            goto error;
        }
    }

    return 0;

    error:
        logger("error", "server_tcp_accept");
        return -1;
}