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

char *allocate(const char* str, int character, int occur){
	char* start, *end, *buffer;
	start = strchr2((const char*)str, (int)character, occur-1);
	end = strchr2((const char*)str, (int)character, occur)-1;
	if(start != NULL && end == NULL) end = (char*)str+strlen(str);
	if(start == NULL) return NULL;
	buffer = (char*)malloc((int)(end-start+1)*sizeof(char));
	strncpy(buffer, start, end-start);
	return buffer;
}

enum http_method getMethod(const char* firstLine, int* err){
	char* allowed_methods[NBRE_METHOD] = {"GET"};
	int i = 0;
	char* buffer;
	buffer = allocate(firstLine, ' ', 1);
	if(buffer == NULL) *err = 1;
	for(i=0; i<NBRE_METHOD; i++){
		if(strcmp(buffer, allowed_methods[i]) == 0){
			free(buffer);
			return HTTP_GET;
		}
	}

	free(buffer);
	return HTTP_UNSUPPORTED;
}

float getVersion(const char *firstLine){
	char *start = "HTTP/1.";
	char *buffer;
	buffer = allocate(firstLine, ' ', 3);
	if(buffer[8] == '\r') buffer[8] = '\0';
	if(strlen(buffer) != 8) return -1.0;
	if(strstr(start, buffer) == buffer || (buffer[7] != '0' && buffer[7] != '1'))
		return -1.0;
	return 1+(buffer[7]-48)*0.1;	
}

char* getRequestURI(const char *firstLine){
	return allocate(firstLine, ' ', 2);
}

int parse_http_request(const char* request_line, http_request* req){
	enum http_method method;
	int err = 0;
	float version;
	method = getMethod(request_line, &err);
	if(err)
		return 0;
	req->method = method;
	version = getVersion(request_line);
	if(version == -1.0) return 0;
	req->version = version;
	if(getRequestURI(request_line) == NULL) return 0;
	req->target = getRequestURI(request_line);
	return 1;
}

int analyze(char *request, http_request* req){
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

	temp = parse_http_request(buffer, req);
	
	if(!temp) return 0;
	return 1;

}
