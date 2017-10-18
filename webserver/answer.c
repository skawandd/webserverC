#include "answer.h"

char* get200(){
	char *buffer = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 9\r\n\r\nBienvenu\n";
	return buffer;
}

char* get400(){
	char *buffer = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\n";
	return buffer;
}

char* get404(){
	char* buffer = "HTTP/1.1 404 Not Found\r\nConnection: close\r\nContent-Length: 14\r\n\r\n404 Not Found\n";
	return buffer;
}

char* getAnswer(int retCode){
	switch(retCode){
		case 200:
			return get200();
		case 400:
			return get400();
		case 404:
			return get404();
	}
	return NULL;
}
