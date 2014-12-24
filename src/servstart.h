#define PORT "8080"
#define BACKLOG 10

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);
void bind_serv(int *socketfd);
void start_listen(int *socketfd);