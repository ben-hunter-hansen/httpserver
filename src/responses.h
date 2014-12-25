static char* OK_RESP =
  "HTTP/1.0 200 OK\n"
  "Server: httpserver/0.2\n"
  "Content-type: text/html\n"
  "\n";


char *get_resource_contents(request_headers headers, route routes[MAX_ROUTES], int n);