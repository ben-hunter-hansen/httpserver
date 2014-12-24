/*
**	main.c
**	Entry point for the http server application
**	Author: Ben Hansen
**	12/21/14
**	ben@bensdevblog.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "servstart.h"
#include "routes.h"
#include "requests.h"
#include "server.h"

int main(int argc, char *argv[]) {

	int sock_fd;

	bind_serv(&sock_fd);
	start_listen(&sock_fd);
	run_server(&sock_fd);

	return EXIT_SUCCESS;
}