#include<unistd.h>
#include<sys/mman.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int fd=open("hello.txt",O_RDWR,0);
	char *buf;
	buf=mmap(NULL,1,PROT_WRITE,MAP_SHARED,fd,0);
	buf[0]='J';
	munmap(buf,1);
	close(fd);
}
