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
	OPTION,
	NOT_VALID
} r_method;

typedef struct REQUEST_HEADERS {
	r_method method;
	char uri[MAX_RURI_LEN];
} request_headers;

request_headers get_header_data(char *header_str);
