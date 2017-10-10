#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define NBRE_METHOD 2
#define GET 0
#define POST 1

char* strchr2(const char* str, int character, int occur);
char* allocate(char*str, int character, int occur);
int getMethod(char* firstLine);
float getVersion(char *firstLine);
char* getRequestURI(char *firstLine);
int analyze(char *request);

#endif
