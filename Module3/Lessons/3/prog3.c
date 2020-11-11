#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>

#define len 10000

int main(void)
{
	int fd;
	size_t length; 
	struct A
	{
		int f;
		int f2;
	};
	fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
	if( fd == -1)
	{
		printf("File open failed!\n");
		exit(1);
	}
	length = len*sizeof(struct A);
	ftruncate(fd,length);
	struct A *ptr = (struct A *)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if( ptr == MAP_FAILED )
	{
		printf("Mapping failed!\n");
		exit(2);
	}
	int q=0;
	for(q = 1; q <=len;q++)
	{
		ptr->f = q;
		ptr->f2 = ptr->f*ptr->f;
		printf("f is %d f2 is %d\n",ptr->f,ptr->f2);
		ptr++;
	}
	munmap((void *)ptr, length);
	return 0;
}
