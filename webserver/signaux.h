#ifndef __SIGNAUX_H__
#define __SIGNAUX_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void traitement_signal(int sig);
void initialiser_signaux();

#endif
