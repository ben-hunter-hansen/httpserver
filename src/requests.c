#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "requests.h"

/*
**	Translates request header string into a structure containing
**	all the header data.
**
**	@param *header_str		The header string
**	@return					The request header structure				
*/
request_headers get_header_data(char *header_str) {
	request_headers req_h;
	char *method, *uri;

	//Begin header string iteration
	int strpos = 0;
	method = malloc(MAX_RMETHOD_LEN);
	uri = malloc(MAX_RURI_LEN);

	get_request_method(header_str, strpos, method);
	strpos += strlen(method) + 1; //Skip over the space: 'GET '.<--strpos

	get_resource_uri(header_str, strpos, uri);
	strpos += strlen(uri) + 1; 

	if(strcmp(method, HTTP_GET) == 0) {
		r_method this_req = GET;
		req_h.method = this_req;
	}

	strcpy(req_h.uri, uri);

	free(method);
	free(uri);

	//do some more parsing..
	return req_h;
}

/*
**	Gets the request method from a header string
**	
**	@param *fullstr		the full header string
**	@param idx			the current position in the header string
**	@param *buff		pointer to the method buffer
*/
void get_request_method(char *fullstr, int idx, char *buf) {
	char *iterator = fullstr;
	int i;
	for(i = 0; *iterator != ' '; i++, iterator++) {
		*(buf + i) = *iterator;
	}
	*(buf + i) = '\0';
}

/*
**	Gets the resource uri from a header string
**	
**	@param *fullstr		the full header string
**	@param idx			the current position in the header string
**	@param *buff		pointer to the uri buffer
*/
void get_resource_uri(char *fullstr, int idx, char *buf) {
	char *iterator = fullstr;
	iterator += idx;
	int i;
	for(i = 0; *iterator != ' '; i++, iterator++) {
		*(buf + i) = *iterator;
	}
	*(buf + i) = '\0';
}