#include "csapp.h"
sigjmp_buf buf;
void handler(int sig)
{
	siglongjmp(buf,1);
}
char* tfgets()
{
	printf("Enter the maximum size of an input line:\n");
	int n;
	scanf("%d",&n);
	char*ans;
	ans=malloc(sizeof(char)*(n+2));
	fgets(ans,n,stdin);//   get rid of /n after the number
	printf("Please type your input line in 5 secs\n");
	if (sigsetjmp(buf,1)) 
	{
		printf("\nHa ha time up!\n");
		return NULL;
	}
	alarm(5);
	fgets(ans,n,stdin);
	return ans;
}
int main()
{
	Signal(SIGALRM,handler);
	char*ans=tfgets();
	if (ans!=NULL) 
	{
		printf("Oh yes, you type this in time!\n");
		printf("%s",ans);
	}
}
