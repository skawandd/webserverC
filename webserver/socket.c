#ifndef __SOCKET_H__
#define __SOCKET_H__
#include "socket.h"

int creer_serveur(int port){

	int socket_serveur = -1;
	int socket_client = -1;
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
	int optval = 1;
	pid_t pid;

	socket_serveur = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_serveur == -1){
		perror("socket_serveur");
		return -1;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if(setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
		perror("Impossible de modifier l'option SO_REUSEADDR\n");

	if(bind(socket_serveur, (struct sockaddr * )&saddr, sizeof(saddr)) == 1){
		perror("bind socket_serveur");
		return -1;
	}

	if(listen(socket_serveur, 10) == -1){
		perror("listen socket_serveur");
		return -1;
	}


	while(1){
		printf("Tentative connexion...\n");
		socket_client = accept(socket_serveur, NULL, NULL);
		
		pid = fork();

		// Traitement pour le pere
		if(pid != 0){
			close(socket_client);
		}else{
			if(socket_client == -1){
				perror("accept");
				return -1;
			}
			
			while(1){
			  	printf("Connexion OK\n");
			  	sleep(1);
			  	write(socket_client, message_bienvenue, strlen(message_bienvenue));
			}

		}

	}

	return 0;

}

void initialiser_signaux(void){
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		perror("signal");
		exit(-1);
	}
}

#endif
