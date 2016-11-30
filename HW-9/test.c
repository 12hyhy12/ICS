#include "csapp.h"
int main()
{
	int fd1,fd2;
	fd1=Open("a.txt",O_RDONLY,0);
	fd2=Open("b.txt",O_RDONLY,0);
	printf("%d\n",fd1);
	Close(fd2);
	printf("%d\n",fd2);
	fd2=Open("c.txt",O_RDONLY,0);
	printf("%d\n",fd2);
	exit(0);
}
