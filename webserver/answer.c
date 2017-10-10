#include "answer.h"

char* get20x(){
	char *buffer = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 10\r\n\r\nBienvenu\n";
	return buffer;
}

char* get40x(){
	char *buffer = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\n";
	return buffer;
}

char* getAnswer(int retCode){
	switch(retCode){
		case 200:
			return get20x();
		case 400:
			return get40x();
	}
	return NULL;
}
