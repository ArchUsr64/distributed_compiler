#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_host(char *file_path)
{
	char buffer[1024 * 16], symbol;
	int i, ret;
	FILE *file_ptr = fopen(file_path, "r");
	if (!file_ptr) {
		printf("[ERROR] Failed to open the file '%s'\n", file_path);
		return EXIT_FAILURE;
	}
	do {
		symbol = getc(file_ptr);
		buffer[i++] = symbol;
		if (i >= sizeof(buffer)) {
			printf("[ERROR] Overflowed buffer for file reading\n");
			return EXIT_FAILURE;
		}
	} while (symbol != EOF);
	fclose(file_ptr);
	printf("[INFO] Successfully read file '%s' into buffer\n", file_path);
	int socket_descriptor = socket_descriptor =
		socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *host = gethostbyname("localhost");
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(1234);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (connect(socket_descriptor, (const struct sockaddr *)&server_address,
		    sizeof(server_address)) != 0) {
		printf("[ERROR] Failed to connect to the server\n");
		return 1;
	};
	ret = send(socket_descriptor, buffer, sizeof(buffer), 0);
	if (ret < 0) {
		printf("[ERROR] Failed to send file buffer to node\n");
		return ret;
	}
	printf("[INFO] Successfully sent file buffer data to node\n");
	close(socket_descriptor);

	return 0;
}
