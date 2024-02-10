// Written for Unix systems
// (Because Unix functions are being used)

#include <stdio.h>
#include <assert.h>


int main()
{
	int fd = open("file.txt", O_RDONLY);
	assert(fd >= 0);
	
	int rc = fork();
	if (rc == 0)
	{
		rc = lseek(fd, 10, SEEK_SET);
		printf("Child: offset - %d\n", rc);
	}
	else
	{
		wait(NULL);
		printf("Parent: offset - %d\n", lseek(fd, 0, SEEK_CUR));
	}
	
	return 0;
}