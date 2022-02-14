#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void * spam (void *spam);

int main (int argc, char **argv) {

	pthread_t threads[1000];	

	int i;

	for (i = 0; i < 20000; i++) {

		pthread_create(&threads[i], NULL, spam, NULL);

	}

	pthread_join(threads[0], NULL);

}

void * spam (void *spam) {

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0) {

		printf("Failed to create socket!\n");

		return NULL;

	}

	struct sockaddr_in server;

	memset(&server, 0, sizeof(server));

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.sin_family = AF_INET;

	server.sin_port = htons(51234);

	if (connect(fd, (struct sockaddr *) &server, sizeof(server)) < 0) {

		printf("Failed to connect\n");

	}

	char buffer[512];

	while (1) {

		char *message = "1000";

		send(fd, message, strlen(message), 0);

		recv(fd, buffer, 512, 0);

		memset(buffer, 0, 512);

	}

	close(fd);

	return NULL;

}
