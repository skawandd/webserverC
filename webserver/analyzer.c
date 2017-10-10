#include "analyzer.h"

char* strchr2(const char* str, int character, int occur){
	int i = 0;
	char *pch = (char*)str;
	for(i=0; i<occur; i++){
		pch = strchr(pch, character);
		if(pch == NULL) return NULL;
	}
	return pch;
} 

char *allocate(char*str, int character, int occur){
	char* end, *buffer;

	end = strchr2((const char*)str, (int)character, occur);
	if(end == NULL) return NULL;
	buffer = (char*)malloc((int)(end-str)*sizeof(char));
	memcpy(buffer, str, str-end);
	return buffer;
}

int getMethod(char* firstLine){
	char* allowed_methods[NBRE_METHOD] = {"GET", "POST"};
	int i = 0;
	char* buffer;
	
	buffer = allocate(firstLine, ' ', 1);
	
	for(i=0; i<NBRE_METHOD; i++){
		if(strcmp(buffer, allowed_methods[i]) == 0) return i;
	}

	free(buffer);
	return -1;
}

float getVersion(char *firstLine){
	char *start = "HTTP/1.";
	char *buffer;

	buffer = allocate(firstLine, ' ', 3);
	if(strlen(buffer) != 8) return -1.0;
	if(strcmp(start, buffer) != 0 || (buffer[7] != '0' && buffer[7] != '1'))
		return -1.0;
	return 1+(buffer[7]-48)*0.1;	
}

char* getRequestURI(char *firstLine){
	return allocate(firstLine, ' ', 2);
}

int analyze(char *request){
	char* crlf = "\r\n";
	char* crlfEnd = "\r\n\r\n";
	char* endHeader, *header, *body;
	char** lines;
	int headerSize = 0, bodySize = 0, count = 0;

	endHeader = strstr(request, crlfEnd);
	if(endHeader == NULL) return 400;
	
	headerSize = (int)(endHeader-request);
	header = (char*)malloc(headerSize*sizeof(char));
	memcpy(header, request, headerSize);
	bodySize = strlen(request)-(int)(endHeader-request);
	body = (char*)malloc(bodySize*sizeof(char));
 	memcpy(body, header, bodySize);

	count = split(header, crlf);
	
	
}
