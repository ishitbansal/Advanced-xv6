#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char **argv)
{
	int pid = fork();
	if (pid < 0)
	{
		printf("fork(): failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (argc < 3)
		{
			printf("error: too few arguments\n");
			exit(0);
		}
		else
		{
			int priority = atoi(argv[1]);
			int pid = atoi(argv[2]);
			set_priority(priority, pid);
			exit(0);
		}
	}
	else
		wait(0);
	exit(0);
}
