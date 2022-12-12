#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(int argc, char* argv[])
{
	double res;
	int i, var;
	int fileDescriptor;
	struct timeval cur_time, new_time;
	
	for (i = 0; i < 5; i++)
	{
		gettimeofday(&cur_time, NULL);
	
		fileDescriptor = open("input.txt", O_RDONLY, S_IRWXU);
		int err = scanf("%d", &var);
		close(fileDescriptor);
		
		gettimeofday(&new_time, NULL);
		
		if (err < 0)
			printf("The error happened.\n");
		
		res += ( (new_time.tv_sec + new_time.tv_usec) - (cur_time.tv_sec + cur_time.tv_usec) );
	}
	
	printf("The total time - %lf , the average time required - %lf\n", res, res / i);
	
	return 0;
}