#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "routes.h"

int get_routes(route routes[MAX_ROUTES]) {

	const int max_pathlen = 256;
	const int max_namelen = 20;

	FILE *fp;
	fp = fopen(ROUTE_CONFIG, "r");

	if(fp == NULL) {
		puts("Unable to open route configuration file.");
		return;
	}

	puts("Verifying route integrity...");
	char ch;
	int count = 0;
	//count number of lines, should be a multiple of 2
	while((ch = fgetc(fp)) != EOF) { 
		if(ch == '\n') {
			count++;
		}
	}

	//ensure the count isn't odd to 'ensure route integrity'
	//thats good enough for now.
	if(count % 2 != 0) {
		puts("Route config failed: odd count of path/name pairs.");
		return;
	}

	puts("Loading routes...");
	int route_count = count / 2;
	
	//go ahead and assign the routes
	rewind(fp);
	int i, len;
	for(i = 0; i < count; i++) {
		fgets(routes[i].path, max_pathlen - 1, fp);
		len = strlen(routes[i].path);
		routes[i].path[len - 1] = '\0';

		fgets(routes[i].name, max_namelen - 1, fp);
		len = strlen(routes[i].name);
		routes[i].name[len - 1] = '\0';
	}
	printf("%d routes assigned.\n", route_count);

	/* For debugging */
	//for(i = 0; i < count / 2; i++) {
	//	printf("PATH: %s\nNAME: %s\n", routes[i].path, routes[i].name);
	//}

	fclose(fp);

	return route_count;
}