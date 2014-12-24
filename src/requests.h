#define MAX_RMETHOD_LEN 6
#define MAX_RURI_LEN 20

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define HTTP_PUT "PUT"
#define HTTP_DELETE "DELETE"
#define HTTP_OPTION "OPTION"

typedef enum {
	GET,
	POST,
	PUT,
	DELETE,
	OPTION
} r_method;

typedef struct REQUEST_HEADERS {
	r_method method;
	char uri[MAX_RURI_LEN];
} request_headers;

request_headers get_header_data(char *header_str);

void get_request_method(char *fullstr, int idx, char *buf);

/* Retrurns requested resource uri from request header */
void get_resource_uri(char *fullstr, int idx, char *buf);
