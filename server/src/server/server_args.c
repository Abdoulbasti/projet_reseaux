#include "server/server_args.h"

uint16_t SERVER_PORT = DEFAULT_PORT;
//uint16_t SERVER_UDP_PORT = DEFAULT_UDP_PORT;
uint16_t SERVER_MULTI_PORT = DEFAULT_MULTI_PORT;

void set_server_port(uint16_t port)
{
    SERVER_PORT = port;
}

uint16_t get_server_port()
{
    return SERVER_PORT;
}

/*void set_server_udp_port(uint16_t port)
{
    SERVER_UDP_PORT = port;
}

uint16_t get_server_udp_port()
{
    return SERVER_UDP_PORT;
}*/

void set_server_multi_port(uint16_t port){
    SERVER_MULTI_PORT = port;
}

uint16_t get_server_multi_port(){
    return SERVER_MULTI_PORT;
}