#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* Function handling the game */
void * game (void *clientFD);


/* Constant string messages sent to the client */
const char *guessMessage = "Guess a number between number 1 to 100 (q to quit): \n";
const char *tooLow = "Your guess was too low!\n";
const char *tooHigh = "Your guess was too high!\n";
const char *win = "You guessed the number!\n";
	

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

	while (clientFD = accept(socketFD, (struct sockaddr *) &client, (socklen_t *) &sinSize)) {
	
	if (clientFD < 0) {

		printf("Failed to connect!\nErrno: %d\n", errno);

		return 1;

	}

	printf("Connected!");


	pthread_t clientThread;

	int *FDPassedToThread = malloc(1);

	*FDPassedToThread = clientFD;

	if (pthread_create(&clientThread, NULL, game, (void *) FDPassedToThread)) {

		printf("Failed to create thread!\n");

	}

	}

	return 0;

}


void * game (void *arg) {

	printf("Inside Thread!\n");

	int clientFD = *((int *) (arg));

	char clientBuffer[512];

	srand(time(NULL));

	int number = rand() % 100 + 1;

	int guess = -1;

	while (1) {

		send(clientFD, guessMessage, strlen(guessMessage), 0);
		recv(clientFD, clientBuffer, 512, 0);

		if (clientBuffer[0] == 'q') {
			break;
		}

		guess = atoi(clientBuffer);

		if (number == guess) {
			send(clientFD, win, strlen(win), 0);
			break;
		}

		if (number > guess) {
			send(clientFD, tooLow, strlen(tooLow), 0);
		}

		if (number < guess) {
			send(clientFD, tooHigh, strlen(tooHigh), 0);
		}

		memset(clientBuffer, 0, 512);

	}

	free(arg);

	printf("Exiting thread!\n");

	return 0;

}
