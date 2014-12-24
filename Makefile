all:
	gcc src/main.c src/servstart.c src/server.c src/routes.c src/requests.c src/responses.c -o httpserver
