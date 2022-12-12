#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


// program to calculate the average time required by OS to handle a system call of reading 0 bytes file

int main(int argc, char* argv[])
{
	double res;
	int i, var;
	int fileDescriptor;
	struct timeval cur_time, new_time;
	
	for (i = 0; i < 100; i++)
	{
		gettimeofday(&cur_time, NULL);
	
		fileDescriptor = open("input.txt", O_RDONLY, S_IRWXU);
		read(fileDescriptor, &var, 0);
		close(fileDescriptor);
		
		gettimeofday(&new_time, NULL);
				
		res += ( (new_time.tv_sec + new_time.tv_usec) - (cur_time.tv_sec + cur_time.tv_usec) );
	}
	
	printf("The total time - %lf , the average time required - %lf\n", res, res / i);
	
	return 0;
}