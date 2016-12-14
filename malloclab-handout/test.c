#include<stdio.h>
int main()
{
	unsigned int a[2];
	a[0]=a[1]=1;
	long long x=4294967296U;
	x*=100;
	*a=10;
	printf("%d %d\n",a[0],a[1]);
}
