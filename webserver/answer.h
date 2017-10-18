#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"

void send_status(FILE* client, int code, const char *reason_phrase);
void send_response(FILE* client, int code, const char* reason_phrase, const char* message_body);
void getAnswer(FILE* client, int retCode, http_request* req);
char* get200();
char* get400();
char* get404();
