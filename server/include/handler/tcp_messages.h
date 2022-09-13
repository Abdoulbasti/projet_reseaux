#ifndef TCP_MESSAGES_H
#define TCP_MESSAGES_H

#include "protocol/protocol.h"
// structure contenu du message [LIST?]
typedef struct listreq_message {
    uint8_t m;
} listreq_t;
// structure contenu du message [NEWPL]
typedef struct newpl_message {
    char id[ID_LEN];
    char port[PORT_LEN];
} newpl_t;
// structure contenu du message [REGIS]
typedef struct regis_message {
    char id[ID_LEN];
    char port[PORT_LEN];
    uint8_t m;
} regis_t;
// structure contenu du message [SIZE?]
typedef struct sizereq_message {
    uint8_t m;
} sizereq_t;
// structure contenu des messages [UPMOV] [RIMOV] [DOMOV] [LEMOV]
typedef struct mov_message {
    char d[D_LEN];
} mov_t;

#endif // TCP_MESSAGES_H