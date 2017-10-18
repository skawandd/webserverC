#include "answer.h"

void send_status(FILE* client, int code, const char *reason_phrase){
	fprintf(client, "HTTP/1.1 %d %s \r\n", code, reason_phrase);
}

void send_response(FILE* client, int code, const char* reason_phrase, const char* message_body){
	send_status(client, code, reason_phrase);
	fprintf(client, "Connection: close\r\nContent-Length: %d\r\n\r\n%s\n", (int)strlen(message_body)+1, message_body);
}

char* get200(){
	char *buffer = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 9\r\n\r\nBienvenu\n";
	return buffer;
}

char* get400(){
	char *buffer = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 16\r\n\r\n400 Bad request\n";
	return buffer;
}

char* get404(){
	char* buffer = "HTTP/1.1 404 Not Found\r\nConnection: close\r\nContent-Length: 14\r\n\r\n404 Not Found\n";
	return buffer;
}

void getAnswer(FILE* client, int retCode, http_request* req){
	if(!retCode)
		send_response(client, 400, 	"Bad Request", "Bad request\r\n");
	else if(req->method == HTTP_UNSUPPORTED)
		send_response(client, 405, "Method Not Allowed", "Method Not Allowed\r\n");
	else if(strcmp(req->target, "/") == 0)
		send_response(client, 200, "OK", "Bienvenu");
	else
		send_response(client, 404, "Not Found", "Not Found\r\n");
}
