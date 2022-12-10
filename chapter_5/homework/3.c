#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{
		printf("Hello\n");
	}
	else												// parent
	{
		for (int i = 0; i < 100000; i++)
			;
		// int rc = wait(NULL);
		printf("Goodbye\n");
	}
	
	return 0;
}