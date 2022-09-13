#ifndef PROTOCOL_H
#define PROTOCOL_H 

#define ID_LEN 8
#define PORT_LEN 4
#define IP_LEN 15
#define XY_LEN 3
#define P_LEN 4
#define D_LEN 3
#define SPACE_LEN 1
#define SPACE " "

#define TYPE_LEN 5
#define END_LEN 3
#define DATA_MAX_LEN 1024

#define END_MESSAGE "***"

#define DUNNO "DUNNO"
#define NEWPL "NEWPL"
#define REGIS "REGIS"
#define START "START"
#define UNREG "UNREG"
#define SIZER "SIZE?"
#define LISTR "LIST?"
#define GAMER "GAME?"
#define UPMOV "UPMOV"
#define DOMOV "DOMOV"
#define LEMOV "LEMOV"
#define RIMOV "RIMOV"
#define IQUIT "IQUIT"
#define GLISR "GLIS?"
#define MALLR "MALL?"
#define SENDR "SENDR"

// structure d'un message tcp brut
typedef struct server_tcp_message {
    char type[TYPE_LEN];
    int data_len;
    char data[DATA_MAX_LEN];
} tcpmessage_t;

#endif // PROTOCOL_H