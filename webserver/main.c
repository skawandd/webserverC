#include "socket.h"

int main(void){
	int port = 8080;
	initialiser_signaux();
	creer_serveur(port);
	return 0;
}
