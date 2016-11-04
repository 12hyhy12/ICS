//Zhang Yuhao
//1500012703
#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define UL unsigned long long
int hit_count,miss_count,eviction_count,s,E,b,open_out,size,delta_hit,delta_miss,delta_eviction,dfn;
char ch[2];
FILE *f;
UL add,one=1;
typedef struct
{
	int lastUsedTime;
	UL tag;
}block;
block *cache_line;
void Find()
{
	delta_hit=delta_miss=delta_eviction=0;
	UL s_id=add>>b&((one<<s)-1),tag=add>>(b+s);
	block *set_st=cache_line+s_id*E,*tmp,*eviction;
	tmp=set_st;
	dfn++;
	for(int i=0;i<E;i++,tmp++)
		if (tmp->lastUsedTime&&tmp->tag==tag)	// if hit
		{
			tmp->lastUsedTime=dfn;
			delta_hit++;
			return;
		}
	tmp=set_st;
	int Mintime=dfn;
	for(int i=0;i<E;i++,tmp++)	// if there is an empty block
	{
		if (tmp->lastUsedTime==0)
		{
			tmp->lastUsedTime=dfn;
			tmp->tag=tag;
			delta_miss++;
			return;
		}
		if (Mintime>tmp->lastUsedTime)	// get the minimum of lastusedtime
		{
			Mintime=tmp->lastUsedTime;
			eviction=tmp;
		}
	}
	delta_miss++;	// if miss and eviction
	delta_eviction++;
	eviction->lastUsedTime=dfn;
	eviction->tag=tag;
}
int main(int argc,char* argv[])
{
	//printf("%d\n",argc);
	if (argc==10) open_out=1;	//Is there '-v' command?
	s=atoi(argv[argc-7]);
	E=atoi(argv[argc-5]);
	b=atoi(argv[argc-3]);
	printf("%d %d %d\n",s,E,b);
	f=fopen(argv[argc-1],"r");
	cache_line=(block*)malloc((1<<s)*E*sizeof(block));
	memset(cache_line,0,sizeof((1<<s)*E*sizeof(block)));
	while (fscanf(f,"%s%llx,%d",ch,&add,&size)!=EOF)
	{
		
		if (open_out) printf("%c %llx,%d",ch[0],add,size);
		if (ch[0]=='M'||ch[0]=='L') 
		{
			Find();
			if (delta_hit) 	//output information
			{
				if (open_out) printf(" hit");
				hit_count++;
			}
			if (delta_miss)
			{
				if (open_out) printf(" miss");
				miss_count++;
			}
			if (delta_eviction)
			{
				if (open_out) printf(" eviction");
				eviction_count++;
			}
		}
		if (ch[0]=='M'||ch[0]=='S') 
		{
			Find();
			if (delta_hit) 	//output information
			{
				if (open_out) printf(" hit");
				hit_count++;
			}
			if (delta_miss)
			{
				if (open_out) printf(" miss");
				miss_count++;
			}
			if (delta_eviction)
			{
				if (open_out) printf(" eviction");
				eviction_count++;
			}
		}
		printf("\n");
		
	}
	printSummary(hit_count, miss_count, eviction_count);
	return 0;
}
