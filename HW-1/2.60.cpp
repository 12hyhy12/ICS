#include<cstdio>
using namespace std;
unsigned replace_byte(unsigned x,int i,unsigned char b)
{
	int shift_w=i<<3;
	unsigned right=x&((1<<shift_w)-1);
	unsigned left=((x>>(shift_w+8)<<8)|b)<<shift_w;
	return right|left;
}
int main()
{
	printf("%x\n",replace_byte(0x12345678,2,0xab));
	printf("%x\n",replace_byte(0x12345678,0,0xab));
	return 0;
}
