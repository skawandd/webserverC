#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include "signaux.h"

#define BUFFER_SIZE 65025

int creer_serveur(int port);
void boucle_serveur(int socket_serveur);
FILE* getNextClient(int socket_serveur);

#endif
