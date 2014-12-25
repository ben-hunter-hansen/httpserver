#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "requests.h"

void get_request_method(char *fullstr, int idx, char *buf);
void get_resource_uri(char *fullstr, int idx, char *buf);
r_method determine_method(char *method_str);



/*
**	Translates request header string into a structure containing
**	all the header data.
**
**	@param *header_str		The header string
**	@return					The request header structure				
*/
request_headers get_header_data(char *header_str) {
	request_headers req_h;

	//Begin header string iteration
	int strpos = 0;

	char method[MAX_RMETHOD_LEN];
	get_request_method(header_str, strpos, method);
	strpos += strlen(method) + 1; //Skip over the space: 'GET '.<--strpos

	char uri[MAX_RURI_LEN];
	get_resource_uri(header_str, strpos, uri);
	strpos += strlen(uri) + 1; 

	//Figure out which request method was sent
	req_h.method = determine_method(method);

	//Copy the resource uri into the header struct
	strcpy(req_h.uri, uri);

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
		if(i == MAX_RMETHOD_LEN - 1) {
			break; //bail out
		} else {
			*(buf + i) = *iterator;
		}
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
		if(i == MAX_RURI_LEN - 1) {
			break; //bail out
		} else {
			*(buf + i) = *iterator;
		}
	}
	*(buf + i) = '\0';
}

/*
**	Determines the request method via string comparison
**	
**	@param *method_str	the request method string
**	@return				request method enumerator
**	@else return		invalid request method type
*/
r_method determine_method(char *method_str) {
	r_method method_actual;

	if(strcmp(method_str, HTTP_GET) == 0) {
		method_actual = GET;
	} else if(strcmp(method_str, HTTP_POST) == 0) {
		method_actual = POST;
	} else if(strcmp(method_str, HTTP_PUT) == 0) {
		method_actual = PUT;
	} else if(strcmp(method_str, HTTP_DELETE) == 0) {
		method_actual = DELETE;
	} else if(strcmp(method_str, HTTP_OPTION) == 0) {
		method_actual = OPTION;
	} else {
		printf("Unable to determine request method: %s is invalid.\n", method_str);
		method_actual = NOT_VALID;
	}

	return method_actual;
}