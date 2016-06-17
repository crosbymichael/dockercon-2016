#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>

int main(int argc, char **argv)
{
	if (argc > 1 && strcmp(argv[1], "--subreaper") == 0) {
		prctl(PR_SET_CHILD_SUBREAPER, 1);
	}
	printf("main() parent %d\n", getpid());

	pid_t pid = fork();
	if (pid == 0) {
		pid_t child = fork();
		if (child == 0) {
			printf("child process %d with parent %d\n", getpid(),
			       getppid());
			sleep(3);
			printf("child process %d with new parent %d\n",
			       getpid(), getppid());
			sleep(2);
			exit(EXIT_SUCCESS);
		}
		sleep(2);
		printf("parent %d exiting\n", getpid());
		exit(EXIT_SUCCESS);
	}

	int status;
	waitpid(pid, &status, 0);
	sleep(1);

	printf("trying to wait on child\n");
	if (waitpid(-1, &status, 0) < 1) {
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("success waiting on the child of my child\n");
}
