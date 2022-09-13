#include "server/server_tcp_send.h"

/**
 *
 * fonction send_mess socket:number type:string message:string len:number
 *
 * envoyer un message du protocol à une socket
 * retourne la taille du message envoyé ( -1 si erreur )
 * 
 */
ssize_t send_mess(int socket, char type[TYPE_LEN], char * message, int len){
    char new_message[TYPE_LEN + len + END_LEN];
    int offset = 0;
    memcpy(new_message, type, TYPE_LEN);
    offset += TYPE_LEN;
    if(len > 0 && message != NULL){
        memcpy(new_message + offset, message, len);
        offset += len;
    }
    memcpy(new_message + offset, END_MESSAGE, END_LEN);
    offset += END_LEN;
    logger("client", "send_tcp (%d) [%s] data_len:%d", socket, type, len);
    return send(socket, new_message, offset, 0);
}

// [GAMES␣n***]
ssize_t send_games(int socket, uint8_t n){
    char message[SPACE_LEN + sizeof(n)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &n, sizeof(n));
    offset += sizeof(n);
    return send_mess(socket, "GAMES", message, offset);
}
// [OGAME␣m␣s***]
ssize_t send_ogame(int socket, uint8_t m, uint8_t s){
    char message[SPACE_LEN + sizeof(m) + SPACE_LEN + sizeof(s)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &s, sizeof(s));
    offset += sizeof(s);
    return send_mess(socket, "OGAME", message, offset);
}
// [REGOK␣m***]
ssize_t send_regok(int socket, uint8_t m){
    char message[SPACE_LEN + sizeof(m)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    return send_mess(socket, "REGOK", message, offset);
}
// [REGNO***]
ssize_t send_regno(int socket){
    return send_mess(socket, "REGNO", NULL, 0);
}
// [UNROK␣m***]
ssize_t send_unrok(int socket, uint8_t m){
    char message[SPACE_LEN + sizeof(m)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    return send_mess(socket, "UNROK", message, offset);
}
// [DUNNO***]
ssize_t send_dunno(int socket){
    return send_mess(socket, "DUNNO", NULL, 0);
}
// [SIZE!␣m␣h␣w***]
ssize_t send_sizeres(int socket, uint8_t m, uint16_t h, uint16_t w){
    uint16_t h_le = htole16(h);
    uint16_t w_le = htole16(w);

    char message[SPACE_LEN + sizeof(m) + SPACE_LEN + sizeof(h) + SPACE_LEN + sizeof(w)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &h_le, sizeof(h_le));
    offset += sizeof(h_le);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &w_le, sizeof(w_le));
    offset += sizeof(w_le);
    return send_mess(socket, "SIZE!", message, offset);
}
// [LIST!␣m␣s***]
ssize_t send_listres(int socket, uint8_t m, uint8_t s){
    char message[SPACE_LEN + sizeof(m) + SPACE_LEN + sizeof(s)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &s, sizeof(s));
    offset += sizeof(s);
    return send_mess(socket, "LIST!", message, offset);
}
// [PLAYR␣id***]
ssize_t send_playr(int socket, char id[ID_LEN]){
    char message[SPACE_LEN + ID_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, id, ID_LEN);
    offset += ID_LEN;
    return send_mess(socket, "PLAYR", message, offset);
}
// [WELCO␣m␣h␣w␣f␣ip␣port***]
ssize_t send_welco(int socket, uint8_t m, uint16_t h, uint16_t w, uint8_t f, char ip[IP_LEN], char port[PORT_LEN]){
    uint16_t h_le = htole16(h);
    uint16_t w_le = htole16(w);

    char message[SPACE_LEN + sizeof(m) + SPACE_LEN + sizeof(h) + SPACE_LEN + sizeof(w) + SPACE_LEN + sizeof(f) +
                 SPACE_LEN + IP_LEN + SPACE_LEN + PORT_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &m, sizeof(m));
    offset += sizeof(m);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &h_le, sizeof(h_le));
    offset += sizeof(h_le);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &w_le, sizeof(w_le));
    offset += sizeof(w_le);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &f, sizeof(f));
    offset += sizeof(f);
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, ip, IP_LEN);
    offset += IP_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, port, PORT_LEN);
    offset += PORT_LEN;
    return send_mess(socket, "WELCO", message, offset);
}
// [POSIT␣id␣x␣y***]
ssize_t send_posit(int socket, char id[ID_LEN], char x[XY_LEN], char y[XY_LEN]){
    char message[SPACE_LEN + ID_LEN + SPACE_LEN + XY_LEN + SPACE_LEN + XY_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, id, ID_LEN);
    offset += ID_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, x, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, y, XY_LEN);
    offset += XY_LEN;
    return send_mess(socket, "POSIT", message, offset);
}
// [MOVE!␣x␣y***]
ssize_t send_moveres(int socket, char x[XY_LEN], char y[XY_LEN]){
    char message[SPACE_LEN + XY_LEN + SPACE_LEN + XY_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, x, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, y, XY_LEN);
    offset += XY_LEN;
    return send_mess(socket, "MOVE!", message, offset);
}
// [MOVEF␣x␣y␣p***]
ssize_t send_movef(int socket, char x[XY_LEN], char y[XY_LEN], char p[P_LEN]){
    char message[SPACE_LEN + XY_LEN + SPACE_LEN + XY_LEN + SPACE_LEN + P_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, x, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, y, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, p, P_LEN);
    offset += P_LEN;
    return send_mess(socket, "MOVEF", message, offset);
}
// [GOBYE***]
ssize_t send_gobye(int socket){
    return send_mess(socket, "GOBYE", NULL, 0);
}
// [GLIS!␣s***]
ssize_t send_glisres(int socket, uint8_t s){
    char message[SPACE_LEN + sizeof(s)];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, &s, sizeof(s));
    offset += sizeof(s);
    return send_mess(socket, "GLIS!", message, offset);
}
// [GPLYR␣id␣x␣y␣p***]
ssize_t send_gplyr(int socket, char id[ID_LEN], char x[XY_LEN], char y[XY_LEN], char p[P_LEN]){
    char message[SPACE_LEN + ID_LEN + SPACE_LEN + XY_LEN + SPACE_LEN + XY_LEN + SPACE_LEN + P_LEN];
    int offset = 0;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, id, ID_LEN);
    offset += ID_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, x, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, y, XY_LEN);
    offset += XY_LEN;
    memcpy(message + offset, SPACE, SPACE_LEN);
    offset += SPACE_LEN;
    memcpy(message + offset, p, P_LEN);
    offset += P_LEN;
    return send_mess(socket, "GPLYR", message, offset);
}
// [MALL!***]
ssize_t send_mallres(int socket){
    return send_mess(socket, "MALL!", NULL, 0);
}
// [SEND!***] 
ssize_t send_sendres(int socket){
    return send_mess(socket, "SEND!", NULL, 0);
}
// [NSEND***]
ssize_t send_nsend(int socket){
    return send_mess(socket, "NSEND", NULL, 0);
}