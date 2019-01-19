#pragma once

#include "base.h"
#include "message.h"

#include <SDL2/SDL_net.h>

#define MAX_NETWORK_SOCKETS 32

typedef struct {
 TCPsocket socket;
} net_port_t;

typedef enum {
 HOST_LOCAL,
 HOST_NETWORK,
} host_type_e;

typedef struct {
 
} connection_t;

typedef struct {
 boolean_t used;
 TCPsocket socket;
} hosted_client_t;

typedef struct {
 SDLNet_SocketSet socketSet;
 TCPsocket socket;
 hosted_client_t clients[MAX_NETWORK_SOCKETS];
} host_t;

typedef struct {
 
} network_t;

void init_network(network_t* network);

void send_message();
void receive_message();
