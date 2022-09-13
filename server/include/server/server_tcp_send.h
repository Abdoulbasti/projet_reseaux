#ifndef SERVER_TCP_SEND_H
#define SERVER_TCP_SEND_H 

#include <endian.h>
#include <arpa/inet.h>

#include "protocol/protocol.h"

// envoyer un message
ssize_t send_mess(int socket, char type[TYPE_LEN], char * message, int len);

// [GAMES␣n***]
ssize_t send_games(int socket, uint8_t n);
// [OGAME␣m␣s***]
ssize_t send_ogame(int socket, uint8_t m, uint8_t s);
// [REGOK␣m***]
ssize_t send_regok(int socket, uint8_t m);
// [REGNO***]
ssize_t send_regno(int socket);
// [UNROK␣m***]
ssize_t send_unrok(int socket, uint8_t m);
// [DUNNO***]
ssize_t send_dunno(int socket);
// [SIZE!␣m␣h␣w***]
ssize_t send_sizeres(int socket, uint8_t m, uint16_t h, uint16_t w);
// [LIST!␣m␣s***]
ssize_t send_listres(int socket, uint8_t m, uint8_t s);
// [PLAYR␣id***]
ssize_t send_playr(int socket, char id[ID_LEN]);
// [WELCO␣m␣h␣w␣f␣ip␣port***]
ssize_t send_welco(int socket, uint8_t m, uint16_t h, uint16_t w, uint8_t f, char ip[IP_LEN], char port[PORT_LEN]);
// [POSIT␣id␣x␣y***]
ssize_t send_posit(int socket, char id[ID_LEN], char x[XY_LEN], char y[XY_LEN]);
// [MOVE!␣x␣y***]
ssize_t send_moveres(int socket, char x[XY_LEN], char y[XY_LEN]);
// [MOVEF␣x␣y␣p***]
ssize_t send_movef(int socket, char x[XY_LEN], char y[XY_LEN], char p[P_LEN]);
// [GOBYE***]
ssize_t send_gobye(int socket);
// [GLIS!␣s***]
ssize_t send_glisres(int socket, uint8_t s);
// [GPLYR␣id␣x␣y␣p***]
ssize_t send_gplyr(int socket, char id[ID_LEN], char x[XY_LEN], char y[XY_LEN], char p[P_LEN]);
// [MALL!***]
ssize_t send_mallres(int socket);
// [SEND!***] 
ssize_t send_sendres(int socket);
// [NSEND***]
ssize_t send_nsend(int socket);

#endif // SERVER_TCP_SEND_H
