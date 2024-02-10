// Written for Unix systems
// (Because Unix functions are being used)

#include <stdio.h>
#include <assert.h>

struct dirent
{
	char d_name[256];				// name of file
	ino_t d_ino;					// inode
	off_t d_off;
	unsigned short d_reclen;
	unsigned char d_type;			// type of file
}


int main()
{
	DIR* dp = opendir(".");		// open the current directory
	assert(dp != NULL);
	
	struct dirent* d;
	while ((d = readdir(dp)) != NULL)
		printf("%lu %s\n", (unsigned long) d->d_ino, d->d_name);
	
	closedir(dp);
	return 0;
}