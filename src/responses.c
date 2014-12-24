#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "routes.h"
#include "requests.h"

/*
**	Determines the requested resource from the route tables and returns
**	a buffer containing the resource contents. 
** 
**	@param headers 		the request headers
**  @param routes 		the route table
**	@param n 			route count
**	@return 			contents of requested resource
*/
char *get_resource_contents(request_headers headers, route routes[MAX_ROUTES], int n) {
	char *fname;
	if(strcmp(headers.uri, "/") == 0) { //default '/'
		fname = PAGE_DEFAULT;
	} else {
		int i, j;
		int found = 0;
		for(i = 0; i < n; i++) {
			char route_name[20] = "/";
			strcat(route_name, routes[i].name);
			if(strcmp(route_name, headers.uri) == 0) {
				printf("Requested route: %s\n", route_name);
				fname = routes[i].path;
				found = 1;
				break;
			}
			memset(route_name, '\0', sizeof(route_name));
			strcpy(route_name, "");
		}

		if(!found) {
			fname = PAGE_404;
		}
	}

	char *buffer = 0;
	long length;
	FILE *fp = fopen(fname, "rb");

	if(fp) {
		fseek(fp, 0, SEEK_END);
	  	length = ftell(fp);
	  	fseek(fp, 0, SEEK_SET);
	  	buffer = malloc(length);

	  	if (buffer)
	  	{
	  		fread (buffer, 1, length, fp);
	  	}
	  	
	  fclose (fp);
	}

	if(buffer) {
		char *fcontent = buffer;
		fcontent[length] = 0; 
		return fcontent;
	} else {
		return "Something went horribly wrong";
	}
}