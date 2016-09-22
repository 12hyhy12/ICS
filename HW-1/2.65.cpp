#include<cstdio>
using namespace std;
unsigned x;
int odd_ones(unsigned x)
{
	/*int w_16=(x>>16)^(x&65536);
	int w_8=(w_16>>8)^(w_16&255);
	int w_4=(w_8>>4)^(w_8&15);
	int w_2=(w_4>>2)^(w_4&3);
	int w_1=(w_2>>1)^(w_2&1)*/

	x=x^(x>>1);
	x=x^(x>>2);
	x=x^(x>>4);
	x=x^(x>>8);
	x=x^(x>>16);
	return x&1;
}
int main()
{
	scanf("%u",&x);
	printf("%d\n",odd_ones(x));
}
