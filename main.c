#include <dirent.h>
#include <stdio.h>

int listdir(const char *path)
{
	printf("Listing entries for [%s]:\n", path);
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path);
	if (!dp) {
		perror("Failed to open directory");
		return -1;
	}

	while ((entry = readdir(dp))) {
		switch (entry->d_type) {
		case DT_DIR:
			printf("D");
			break;
		case DT_REG:
			printf("F");
			break;
		default:
			printf("U");
			break;
		}
		printf("\t %s\n", entry->d_name);
	}

	closedir(dp);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		listdir(".");
	} else {
		for (int i = 1; i < argc; i++) {
			listdir(argv[i]);
		}
	}
	return 0;
}
