#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	if (mkfifo("exit-fifo", 0666) != 0) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	int fd = open("exit-fifo", O_WRONLY | O_CLOEXEC, 0);
	if (fd < 0) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pause();
}
