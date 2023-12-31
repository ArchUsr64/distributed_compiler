#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define OUT_PATH "out.c"
#define COMPILE_COMMAND "gcc -c "OUT_PATH

int run_node()
{
	int bind_descriptor, socket_descriptor, accept_descriptor;
	char buffer[1024 * 16];
	struct sockaddr_in client_address, server_address;
	int client_len = sizeof(client_address);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(1234);
	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	bind_descriptor = bind(socket_descriptor,
			       (const struct sockaddr *)&server_address,
			       sizeof(server_address));

	listen(socket_descriptor, 5);
	printf("Server is running...\n");
	while (1) {
		int i;
		printf("Waiting for connection...\n");
		accept_descriptor = accept(socket_descriptor,
					   (struct sockaddr *)&server_address,
					   (socklen_t *)&client_len);

		printf("Connection received...\n");
		int bytes_read =
			recv(accept_descriptor, buffer, sizeof(buffer), 0);
		printf("Received file data:\n\n");
		for (i = 0; i < bytes_read && buffer[i] != EOF; i++) {
			printf("%c", buffer[i]);
		}

		FILE *file_ptr = fopen(OUT_PATH, "w");
		if (!file_ptr) {
			printf("[ERROR] Failed to open file: '%s'\n", OUT_PATH);
			return EXIT_FAILURE;
		}
		fwrite(buffer, 1, i, file_ptr);
		fclose(file_ptr);

		close(accept_descriptor);

		printf("Compiling the received file\n");
		system(COMPILE_COMMAND);
		printf("\n");
	}

	return EXIT_SUCCESS;
}
