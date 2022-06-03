#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int checkWin (char *input);

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


	/* Receive data */

	char serverBuffer[2000];

	char inputBuffer[2000];

	
	while (1) {

		/* Receive initial message */
	
		memset(serverBuffer, 0, 2000);

		recv(socketFD, serverBuffer, 2000, 0);
		printf("%s", serverBuffer);

		if (checkWin(serverBuffer)) {

			break;

		}

		/* Read guess from the client and send */

		memset(inputBuffer, 0, 2000);
		scanf("%s", inputBuffer);

		send(socketFD, inputBuffer, 512, 0);

		if (inputBuffer[0] == 'q') {
			break;
		}

		/* Read the guess too high or guess too low */

		memset(serverBuffer, 0, 2000); 

/*
		recv(socketFD, serverBuffer, 2000, 0);
		printf("%s", serverBuffer);

		if (strcmp(serverBuffer, winMessage) == 0) {

			break;	

		}

	*/

	}

	return 0;

}


int checkWin(char *input) {

	char *winMessage = "You guessed the number!\n";

	int i;

	for (i = 0; i < strlen(winMessage); i++) {

		if (winMessage[i] != input[i]) {

			return 0;

		}

	}

	return 1;

}
