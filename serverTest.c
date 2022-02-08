#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main (int argc, char **argv) {

	/* Create Socket */

	int socketFD;
	socketFD = socket(AF_INET, SOCK_STREAM, 0);	

	if (socketFD == -1) {

		printf("Failed to create socket!");

	}


	/* Set up the server struct */

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(51234);

	/* Bind the socket to the server */

	if (bind(socketFD, (struct sockaddr *) &server, sizeof(server)) < 0) {

		printf("Failed to bind socket");
	
	}

	
	/* Listen for up to 3 connections */

	listen(socketFD, 3);

	/* Accept a connection */

	struct sockaddr_in client;
	int clientFD;
	int sinSize = sizeof(server);
	memset(&client, 0, sizeof(client));
	clientFD = accept(socketFD, (struct sockaddr *) &server, (socklen_t *) &sinSize);
	
	if (clientFD < 0) {

		printf("Failed to connect!\nErrno: %d\n", errno);

		return 1;

	}

	printf("Connected!");

	char clientBuffer[2000];

	recv(clientFD, clientBuffer, 2000, 0);

	if (clientBuffer[0] == '1') {

		char *message = "You chose option 1";

		send(clientFD, message, strlen(message), 0);

	} else {

		char *message = "You did not choose option 1";

		send(clientFD, message,strlen(message), 0);

	}


	return 0;

}
