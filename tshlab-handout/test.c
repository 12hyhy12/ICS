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
	Signal(SIGALRM,handler);
	Alarm(5);
	if (sigsetjmp(buf,1)) 
	{
		printf("ha ha time up!\n");
		return NULL;
	}
	while (1);
	char*ans;
	ans=malloc(sizeof(char)*(n+2));
	fgets(ans,n,stdin);
	return ans;
}
int main()
{
	char*ans=tfgets();
	if (ans!=NULL) 
	{
		printf("Oh yes, you type this in time!\n");
		printf("%s",ans);
	}
}
