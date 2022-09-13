#ifndef SERVER_TCP_MESSAGE_H
#define SERVER_TCP_MESSAGE_H 

int dunno(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int newpl(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int regis(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int start(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int unreg(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int sizereq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int listreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int gamereq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int upmov(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int domov(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int lemov(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int rimov(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int iquit(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int glisreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int mallreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);
int sendreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message);

#include "../src/handler/messages/dunno.c"

#include "../src/handler/messages/lobby/newpl.c"
#include "../src/handler/messages/lobby/regis.c"

#include "../src/handler/messages/lobby/start.c"
#include "../src/handler/messages/lobby/unreg.c"

#include "../src/handler/messages/request/sizereq.c"
#include "../src/handler/messages/request/listreq.c"
#include "../src/handler/messages/request/gamereq.c"

#include "../src/handler/messages/mov/mov.c"
#include "../src/handler/messages/mov/upmov.c"
#include "../src/handler/messages/mov/domov.c"
#include "../src/handler/messages/mov/lemov.c"
#include "../src/handler/messages/mov/rimov.c"

#include "../src/handler/messages/iquit.c"

#include "../src/handler/messages/request/glisreq.c"
#include "../src/handler/messages/request/mallreq.c"
#include "../src/handler/messages/request/sendreq.c"

#endif // SERVER_TCP_MESSAGE_H