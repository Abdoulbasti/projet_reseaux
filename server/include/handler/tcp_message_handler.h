#ifndef TCP_MESSAGE_HANDLER_H
#define TCP_MESSAGE_HANDLER_H

#include <string.h>

#include "protocol/protocol.h"
#include "handler/tcp_messages.h"

// structure d'un handler de message
typedef struct message_handler
{
    char type[TYPE_LEN];
    int (*func_manager)(int *socket, struct sockaddr_in *address, tcpmessage_t *message);
} messageh_t;

// gérer les messages à traiter
int tcp_message_handler(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
// (auxiliaire) ajouter un messages à traiter
int add_handler_aux(int socket, messageh_t *message_handler);
// ajouter un message à traiter
int add_handler(int socket, char type[TYPE_LEN], int (*func_manager)(int *socket, struct sockaddr_in *address, tcpmessage_t *message));
// retirer un message à traiter
int remove_handler(int socket, char type[TYPE_LEN]);
// néttoyer les message à traiter
int clear_handler(int socket);
// convertir une valeur en texte
char *u16_to_str(uint16_t value, char *str, int len);
// convetir un texte en valeur
uint16_t str_to_u16(char * str, int len);
// convertir une structure sockaddr en text
char * ip_to_str(struct sockaddr * ip);

#endif // TCP_MESSAGE_HANDLER_H