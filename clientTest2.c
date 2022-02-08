#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main (int argc, char **argv) {
	
	/* Socket Descriptor */
	int socketFD;

	/* Struct represents the server */ 
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));

	
	/* Creates the socket using IPv4 and TCP */
	socketFD = socket(AF_INET, SOCK_STREAM, 0);

	if (socketFD == -1) {

		printf("Could not create socket.");

	}

	/* Setup the server data */

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(51234);

	/* Connect to the server */

	if (connect(socketFD, (struct sockaddr *)&server, sizeof(server)) < 0) {

	printf("Connection error");

	return 0;
		
	}

	printf("Connected!\n");


	/* Message */

	char *message = "2";

	/* Send data to the server */

	if (send(socketFD, message, strlen(message), 0) < 0) {

		printf("Could not send data!");

	}

	printf("Data Sent!\n");

	
	/* Receive data */

	char buffer[100000];

	if (recv(socketFD, buffer, 6000, 0) < 0) {

		printf("Could not receive data!\n");

	}
	
	printf("%s", buffer);

	return 0;

}

