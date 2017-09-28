#include "socket.h"

int creer_serveur(int port){

	int socket_serveur = -1;
	int optval = 1;

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

	boucle_serveur(socket_serveur);

	return 0;

}

void boucle_serveur(int socket_serveur){

	FILE* client;
	pid_t pid;
	const char *message_bienvenue = "<pawnee>\n";
	char buffer[BUFFER_SIZE];

	while(1){
		printf("Tentative connexion...\n");

		client = getNextClient(socket_serveur);

		pid = fork();

		// Traitement pour le pere
		if(pid != 0){
			fclose(client);
		}else{
			if(client == NULL){
				perror("FILE");
				return;
			}
		
			fprintf(stderr, "%d\n", getpid());

			while(fgets(buffer, BUFFER_SIZE, client) > 0){
				strcat(buffer, message_bienvenue);
				fprintf(client, "%s", buffer);
			}

			exit(0);

		}
		wait(&pid);
	}

}

FILE* getNextClient(int socket_serveur){
	int socket_client = -1;
	FILE* client;
	socket_client = accept(socket_serveur, NULL, NULL);
	client = fdopen(socket_client, (const char*)"w+");
	return client;
}
