#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <signal.h>

#include "servstart.h"

void sigchld_handler(int s) {
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void bind_serv(int *socketfd) {

	int sockfd = *socketfd;
	int rv;
	int yes = 1;

	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //use my ip

	if((rv = getaddrinfo(NULL,PORT, &hints, &servinfo))!= 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	}

	// loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
    	if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
    		perror("server: socket");
    		continue;
    	}

    	if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    		perror("setsockopt");
    		exit(1);
    	}

    	if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
    		close(sockfd);
    		perror("server: bind");
    		continue;
    	}

    	break;
    }

    if(p == NULL) {
    	fprintf(stderr, "server: failed to bind\n");
    }

    *socketfd = sockfd; //return socket file descriptor to main prog
    freeaddrinfo(servinfo); //all done with this structure
}

void start_listen(int *socketfd) {
	
	int sockfd = *socketfd;
	struct sigaction sa;

	if(listen(sockfd, BACKLOG) == -1) {
    	perror("listen");
    	exit(1);
    }

    sa.sa_handler = sigchld_handler; //reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCLD, &sa, NULL) == -1) {
    	perror("sigaction");
    	exit(1);
    }
}