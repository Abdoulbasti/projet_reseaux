#include "handler/tcp_message_handler.h"

bst_node_t *client_handlers = NULL;

char * ip_to_str(struct sockaddr * ip){
    struct sockaddr_in * ipv4 = (struct sockaddr_in *)ip;
    char * ip_res = (char *)malloc(sizeof(char) * IP_LEN);
    memset(ip_res, '#', sizeof(char) * IP_LEN);
    char * ip_str = inet_ntoa(ipv4->sin_addr); 
    memcpy(ip_res, ip_str, strlen(ip_str));
    return ip_res;
}

/**
 *
 * fonction _pow10 n:number
 *
 * retourne 10^n
 * 
 */
int _pow10(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return 10 * _pow10(n - 1);
}

/**
 *
 * fonction type_to_int type:string
 *
 * retourne les 4 dernier octets en tant qu'entier
 * 
 */
unsigned int type_to_int(char type[TYPE_LEN])
{
    unsigned int r = 0;
    memcpy(&r, type + 1, sizeof(unsigned int));
    return r;
}

/**
 *
 * fonction u16_to_str value:number str:string len:number
 *
 * retourne une string
 * 
 */
char *u16_to_str(uint16_t value, char *str, int len)
{
    for (int i = 0; i < len; i++)
    {
        int m = len - i;
        int k = (value % _pow10(m)) / _pow10(m - 1);
        str[i] = '0' + k;
    }
    return str;
}

/**
 *
 * fonction str_to_u16 str:string len:number
 *
 * retourne un entier
 * 
 */
uint16_t str_to_u16(char * str, int len)
{
    uint16_t result = 0;
    for (int i = 0; i < len; i++)
    {
        int m = len - i;
        result += (str[i] - '0') * _pow10(m - 1);
    }
    return result;
}

/**
 *
 * fonction tcp_message_handler client_socket:* address:* message:*
 *
 * gère la gestion d'un message reçu par un client
 * retourne un entier
 * 
 */
int tcp_message_handler(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client", "(%d) %s:%d receive message - type: %s data_len: %d",
           *client_socket,
           inet_ntoa(address->sin_addr),
           htons(address->sin_port),
           message->type,
           message->data_len);
    if (client_handlers != NULL)
    {
        // récupération du noeud de la socket
        bst_node_t *client = search(client_handlers, *client_socket);

        if (client != NULL)
        {
            if (client->value != NULL)
            {   
                // récupération du handler du message à partir de son type
                bst_node_t *handler_node = search((bst_node_t *)client->value, type_to_int(message->type));
                // si on a trouver un handler correspondant au type du message
                if (handler_node != NULL)
                {   
                    // éxécution du handler
                    return ((messageh_t *)handler_node->value)->func_manager(client_socket, address, message);
                }
                else
                {
                    // pas de handler trouvé pour le message -> dunno
                    return dunno(client_socket, address, message);
                }
            }
            else
            {
                // pas de handler trouvé pour le message -> dunno
                return dunno(client_socket, address, message);
            }
        }
        else
        {
            // pas de client trouvé -> dunno
            return dunno(client_socket, address, message);
        }
    }
    else
    {
        // pas de liste de handler -> dunno
        return dunno(client_socket, address, message);
    }
}

/**
 *
 * fonction add_handler_aux socket:number message_handler:*
 * 
 * [AUX]
 * ajouter un handler sur un client
 * retourne 0
 * 
 */
int add_handler_aux(int socket, messageh_t *message_handler)
{
    unsigned int message_id = type_to_int(message_handler->type);
    if (client_handlers == NULL)
    {
        bst_node_t *message_handlers = new_bst(message_id, message_handler);
        client_handlers = new_bst(socket, message_handlers);
        logger("client-handler", "add_handler (%s) - client (%d)", message_handler->type, socket);
        return 0;
    }
    else
    {
        bst_node_t *client = search(client_handlers, socket);

        if (client != NULL)
        {
            if (client->value != NULL)
            {
                bst_node_t *message_handlers = (bst_node_t *)client->value;
                insert_bst(message_handlers, message_id, message_handler);
            }
            else
            {
                client->value = new_bst(message_id, message_handler);
            }
        }
        else
        {
            insert_bst(client_handlers, socket, new_bst(message_id, message_handler));
        }

        logger("client-handler", "add_handler (%s) - client (%d)", message_handler->type, socket);
        return 0;
    }
}

/**
 *
 * fonction add_handler_aux socket:number type:string func_manager:*
 *
 * ajouter un handler sur un client
 * retourne 0
 * 
 */
int add_handler(int socket, char type[TYPE_LEN], int (*func_manager)(int *socket, struct sockaddr_in *address, tcpmessage_t *message))
{
    messageh_t *m = (messageh_t *)malloc(sizeof(messageh_t));
    memcpy(m->type, type, TYPE_LEN);
    m->func_manager = func_manager;
    return add_handler_aux(socket, m);
}

/**
 *
 * fonction remove_handler socket:number type:string
 *
 * supprimer un handler sur un client
 * retourne 0
 * 
 */
int remove_handler(int socket, char type[TYPE_LEN])
{
    bst_node_t *client = search(client_handlers, socket);

    if (client != NULL)
    {
        if (client->value != NULL)
        {
            unsigned int message_id = type_to_int(type);
            bst_node_t *message_handlers = (bst_node_t *)client->value;

            while (search(message_handlers, message_id) != NULL)
            {
                client->value = delete_bst(message_handlers, message_id);
            }
            logger("client", "remove_handler (%s) - client (%d)", type, socket);
            return 0;
        }
    }

    return -1;
}

/**
 *
 * fonction clear_handler socket:number
 *
 * supprimer un client de la liste des handlers
 * retourne 0
 * 
 */
int clear_handler(int socket)
{
    bst_node_t *client = search(client_handlers, socket);

    if (client != NULL)
    {
        if (client->value != NULL)
        {
            while (client->value != NULL)
            {
                bst_node_t *message_handlers = (bst_node_t *)client->value;
                client->value = delete_bst(message_handlers, message_handlers->id);
            }
        }

        client_handlers = delete_bst(client_handlers, socket);
        logger("client", "clear_handler - client (%d)", socket);
        return 0;
    }

    return -1;
}