#include "signaux.h"

void traitement_signal(int sig){
	waitpid(-1, &sig, WNOHANG);
}

void initialiser_signaux(void){

	struct sigaction sa;
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &sa, NULL) == -1){
		perror("sigaction(SIGCHLD)");
		exit(-1);
	}

	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		perror("signal");
		exit(-1);
	}
}
