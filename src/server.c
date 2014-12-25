#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "servstart.h"
#include "routes.h"
#include "requests.h"
#include "responses.h"
#include "server.h"

/*
**	Begin accepting client connections. 
**	
**	@param *sockfd 	The socket file descriptor
*/
void run_server(int *socketfd) {

	int sock_fd;
	sock_fd = *socketfd;

    route routes[MAX_ROUTES];
	int tot_routes = get_routes(routes);

	puts("***** SERVER STARTED *****");
	while(ACCEPTING) {

        struct sockaddr_storage their_addr;
        socklen_t sin_size;
    	sin_size = sizeof their_addr;

        int new_fd;
    	new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);

    	if(new_fd == -1) {
    		perror("accept");
    		continue;
    	}

        char s[INET6_ADDRSTRLEN];
    	inet_ntop(their_addr.ss_family,
    		get_in_addr((struct sockaddr *)&their_addr),
    		s, sizeof s);

    	printf("server: got connection from  %s\n", s);

    	if(!fork()) { //this is the child process
    		close(sock_fd);//child doesn't need the listener

            int numbytes;
            char req_heads[MAXDATASIZE];
    		if((numbytes = recv(new_fd, req_heads, MAXDATASIZE-1, 0)) == -1) {
				perror("recv");
			}
			req_heads[numbytes] = '\0';
			request_headers parsed_h = get_header_data(req_heads);

            //Determine response
            if(parsed_h.method == GET) {
                if(send(new_fd, OK_RESP, strlen(OK_RESP), 0) == -1) {
                    perror("send");
                }

                char *msg = get_resource_contents(parsed_h, routes, tot_routes);
                if(send(new_fd, msg, strlen(msg), 0) == -1) {
                    perror("send");
                }

                free(msg);
            }
    		close(new_fd);
    		exit(0);
    	}
    	close(new_fd); //parent doesn't need this
    }	
}