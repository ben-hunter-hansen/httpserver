#define MAX_ROUTES 100
#define ROUTE_CONFIG "routes.txt"

typedef struct ROUTE {
	char path[256];
	char name[20];
} route;

int get_routes(route routes[MAX_ROUTES]);