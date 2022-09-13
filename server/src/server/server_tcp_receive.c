#include "server/server_tcp_receive.h"

pthread_mutex_t recv_mut = PTHREAD_MUTEX_INITIALIZER;

/**
 *
 * fonction check_str src:string check:string src_len:number
 *
 * vérifie sur une string est présent dans une autre string
 * retourne le pointeur du premier character si la string a était trouvé ( sinon NULL si la string n'a pas était trouvé )
 * 
 */
char *check_str(char *src, const char *check, int src_len)
{
    int check_len = strlen(check);
    int i = 0;

    // fonction pour comparer 2 strings octets par octets
    int check_i()
    {
        for (int k = 0; k < check_len; k++)
        {
            if (i + k >= src_len || src[i + k] != check[k])
            {
                return -1;
            }
        }
        return 1;
    }

    // recherche de la string
    while (i < src_len)
    {
        if (check_i() > 0)
        {
            return &src[i];
        }
        i++;
    }
    return NULL;
}

/**
 *
 * fonction server_tcp_receive arg:*
 *
 * reçois et traite chaque message reçu par un client 
 * retourne NULL
 * 
 */
void *server_tcp_receive(void *arg)
{
    server_accept_t *args = (server_accept_t *)arg;
    logger("client", "(%d) %s:%d connect", args->socket, inet_ntoa(args->address.sin_addr), htons(args->address.sin_port));

    // ajouts des handlers pour les messages qu'on peut recevoir
    add_handler(args->socket, NEWPL, newpl);
    add_handler(args->socket, REGIS, regis);
    add_handler(args->socket, SIZER, sizereq); // SIZE?
    add_handler(args->socket, LISTR, listreq); // LIST?
    add_handler(args->socket, GAMER, gamereq); // GAME?

    // envoye du nombre de jeu disponible [GAMES]
    send_games(args->socket, games_count(0));
    // fonction pour envoyer OGAME au client
    void *send_ogame_element(void *acc, bst_node_t *node)
    {
        game_t *game = (game_t *)node->value;
        if ((game->state & READY) != READY)
        {   
            // envoye du nombre de joueurs dans le jeu [OGAME]
            send_ogame(args->socket, (uint8_t)node->id, entities_count(game, PLAYER));
        }
        return acc;
    }
    games_loop(NULL, send_ogame_element);

    ssize_t recv_len;
    char buffer[BUFFER_MAX_LEN];
    memset(buffer, 0, BUFFER_MAX_LEN);
    ssize_t offset = 0;
    // début réception
    while ((recv_len = recv(args->socket, buffer + offset, BUFFER_LEN, 0)) > 0)
    {
        // mise à jour de la taille du buffer
        offset += recv_len;

        // si le buffer à était remplie sans avoir de message -> déconnecte le client
        if (offset >= BUFFER_MAX_LEN - BUFFER_LEN)
        {
            logger("error", "client (%d) %s:%d BUFFER_MAX_LEN reached", inet_ntoa(args->address.sin_addr),
                   htons(args->address.sin_port),
                   args->socket);
            goto disconnect;
        }

        char *end_ptr;
        int end_ptr_pos = 0;
        // extraction du message
        while ((end_ptr = check_str(buffer + end_ptr_pos, END_MESSAGE, offset - end_ptr_pos)) != NULL)
        {
            // position de la fin du offset
            int new_end_ptr_pos = (end_ptr - buffer);
            // taille du message à extraire
            int len = new_end_ptr_pos - end_ptr_pos;
            // si le message possède bien un type de taille 5
            if (len >= TYPE_LEN)
            {
                tcpmessage_t message; // création du message
                memset(&message, 0, sizeof(message));
                memcpy(message.type, buffer + end_ptr_pos, TYPE_LEN);
                message.data_len = len - TYPE_LEN; // définition de la taille du contenu du message
                if (message.data_len > 0)
                {
                    memcpy(message.data, buffer + end_ptr_pos + TYPE_LEN, message.data_len);
                }

                pthread_mutex_lock(&recv_mut);
                int r = args->message_handler(&args->socket, &args->address, &message); // éxécution du handler du message
                pthread_mutex_unlock(&recv_mut);
                switch (r)
                {
                case 0: // dunno
                    logger("client-handler", "(%d) %s return (0) - send_dunno", args->socket, message.type);
                    send_dunno(args->socket);
                    break;
                case -1: // déconnect
                    logger("client-handler", "(%d) %s return (-1) - disconnect", args->socket, message.type);
                    goto disconnect;
                default: // ok
                    break;
                }
            }
            // cas ou le message n'est pas conforme au message du protocol
            else
            {
                send_dunno(args->socket);
            }

            // ajoute la taille de la string de fin à la taille du message
            end_ptr_pos = new_end_ptr_pos + END_LEN;
        }

        // si un message à était traiter
        if (end_ptr_pos > 0)
        {
            offset -= end_ptr_pos; // retirer la taille du message à la taille total du buffer
            memcpy(buffer, buffer + end_ptr_pos, offset); // supprimer les données traiter du buffer
            memset(buffer + offset, 0, BUFFER_MAX_LEN - offset);
        }
    }
    
    if (recv_len == 0)
    {
        goto disconnect;
    }
    else
    {
        goto error;
    }

disconnect:
    logger("client", "(%d) %s:%d disconnect", args->socket, inet_ntoa(args->address.sin_addr), htons(args->address.sin_port));
    clear_handler(args->socket);
    remove_entity(args->socket);
    close(args->socket);
    free(arg);
    return NULL;

error:
    logger("client", "(%d) %s:%d disconnect (from recv error)", args->socket, inet_ntoa(args->address.sin_addr), htons(args->address.sin_port));
    clear_handler(args->socket);
    remove_entity(args->socket);
    close(args->socket);
    free(arg);
    return NULL;
}