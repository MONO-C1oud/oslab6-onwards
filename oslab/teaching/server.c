// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8080


void handle_connection(int new_socket) {
	char* hello = "Hello from the server!";
	char buffer[1234] = { 0 };
	int valread = read(new_socket, buffer, 1234);
	printf("%s\n", buffer);
	
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// closing the connected socket
	close(new_socket);

}


int main(int argc, char const* argv[]) {

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,	sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 34) < 0) {
		perror("An error occurred while listening");
		exit(EXIT_FAILURE);
	}

	pthread_t t[34];
	int i = 0;
	while (1) {
		printf("Listening for a connection...\n");
		if ((new_socket	= accept(server_fd, (struct sockaddr*)&address,	(socklen_t*)&addrlen)) < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("Connection Accepted!!!\n");

		pthread_create(&t[i], NULL, handle_connection, new_socket);
		i++;
	}

	for (int j = 0; j < i; j++) {
		pthread_join(t[i], NULL);
	}

	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);

	return 0;
}