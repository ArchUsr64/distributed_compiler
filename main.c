#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define is_source_file(file_name)                     \
	((file_name)[strlen(file_name) - 2] == '.' && \
	 (file_name)[strlen(file_name) - 1] == 'c')

const char STRING_BUFFER_TERMINATOR = 0x85;

int get_source_file_name(const char *path, char *buffer)
{
	unsigned buffer_index = 0;
	struct dirent *entry;
	DIR *dp;
	int ret;

	dp = opendir(path);
	if (!dp)
		return -1;

	while ((entry = readdir(dp))) {
		if (entry->d_type == DT_REG && is_source_file(entry->d_name)) {
			strcpy(buffer + buffer_index, entry->d_name);
			buffer_index += strlen(entry->d_name) + 1;
		}
	}

	ret = closedir(dp);
	if (ret) {
		return ret;
	}

	return 0;
}

int main(int argc, char **argv)
{
	int ret;
	char buffer[255];
	memset(buffer, STRING_BUFFER_TERMINATOR, ARRAY_SIZE(buffer));
	ret = get_source_file_name(".", buffer);
	if (ret) {
		perror("Failed to get file names for C source files\n");
		return ret;
	}
	for (char *file_name = buffer; *file_name != STRING_BUFFER_TERMINATOR;
	     file_name++) {
		printf("%s\n", file_name);
		file_name += strlen(file_name);
	}
	return 0;
}
