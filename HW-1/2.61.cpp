#include<cstdio>
using namespace std;
int main()
{
	int T;
	printf("Enter the number of test case(s):\n");
	scanf("%d",&T);
	unsigned x;
	while (T--)
	{
		printf("Enter x(int):\n");
		if (!scanf("%u",&x)) break;
		printf("A:%d\n",!!x);
		printf("B:%d\n",!!(x^(-1)));
		printf("C:%d\n",!!(x&255));
		printf("D:%d\n",!!((x>>((sizeof(int)-1)<<3))^255));
	}
}
