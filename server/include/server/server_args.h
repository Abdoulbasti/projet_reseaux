#ifndef SERVER_ARGS_H
#define SERVER_ARGS_H 

#define DEFAULT_PORT 6666
//#define DEFAULT_UDP_PORT 6667
#define DEFAULT_MULTI_PORT 6987
//#define DEFAULT_UDP_IP "255.255.255.24"

void set_server_port(uint16_t port);
//void set_server_udp_port(uint16_t port);
void set_server_multi_port(uint16_t port);
//void set_server_udp_ip(char *ip);

uint16_t get_server_port();
//uint16_t get_server_udp_port();
uint16_t get_server_multi_port();
//char *get_server_udp_ip();

#endif // SERVER_ARGS_H