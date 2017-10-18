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

enum http_method{
	HTTP_GET,
	HTTP_UNSUPPORTED,
};

typedef struct{
	enum http_method method;
	float version;
	char* target;
} http_request;

char* strchr2(const char* str, int character, int occur);
char* allocate(const char*str, int character, int occur);
enum http_method getMethod(const char* firstLine, int* err);
float getVersion(const char *firstLine);
char* getRequestURI(const char *firstLine);
int parse_http_request(const char* request_line, http_request *req);
int analyze(char *request, http_request* req);

#endif
