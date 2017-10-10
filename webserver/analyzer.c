#include "analyzer.h"

char* strchr2(const char* str, int character, int occur){
	int i = 0;
	char *pch = (char*)str;
	for(i=0; i<occur; i++){
		pch = strchr(pch, character)+1;
		if(pch == NULL) return NULL;
	}
	return pch;
} 

char *allocate(char* str, int character, int occur){
	char* start, *end, *buffer;
	start = strchr2((const char*)str, (int)character, occur-1);
	end = strchr2((const char*)str, (int)character, occur)-1;
	if(start != NULL && end == NULL) end = str+strlen(str);
	if(start == NULL) return NULL;
	buffer = (char*)malloc((int)(end-start+1)*sizeof(char));
	strncpy(buffer, start, end-start);
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
	if(buffer[8] == '\r') buffer[8] = '\0';
	if(strlen(buffer) != 8) return -1.0;
	if(strstr(start, buffer) == buffer || (buffer[7] != '0' && buffer[7] != '1'))
		return -1.0;
	return 1+(buffer[7]-48)*0.1;	
}

char* getRequestURI(char *firstLine){
	return allocate(firstLine, ' ', 2);
}

int analyze(char *request){
	char* crlf = "\r\n";
	char* endHeader, *header, *body, *buffer;
	int headerSize = 0, bodySize = 0, temp;

	endHeader = strstr(request, (const char*)"\r\n\r\n");
	if(endHeader == NULL) endHeader = strstr(request, (const char*)"\r\n\n");
	fprintf(stdout, "%s\n", request);
	if(endHeader == NULL) return 400;
	
	headerSize = (int)(endHeader-request);
	header = (char*)malloc(headerSize*sizeof(char));
	memcpy(header, request, headerSize);
	bodySize = strlen(request)-(int)(endHeader-request);
	body = (char*)malloc(bodySize*sizeof(char));
 	memcpy(body, header, bodySize);
	
	temp = strstr(header, crlf)-header+1;
	buffer = (char*)malloc(temp); 
	memcpy(buffer, header, temp);
	buffer[temp+1] = '\0';

	if(getMethod(buffer) == -1) return 400;
	if( !(getVersion(buffer) != 1.0 && getVersion(buffer) != 1.1) ) return 400;

	return 200;	

}
