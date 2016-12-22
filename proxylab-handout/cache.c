#include <stdio.h>
#include "cache.h"
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define MAX_CACHE_OBJECT 100

typedef struct
{
	char*buf;
	char*flag;
	int timeFlag;
}block;
static block cache[MAX_CACHE_OBJECT];
static int now;
static int timeFlag;
void initCache()//initialize the block
{
	now=0;
	timeFlag=0;
	int i;//make gcc happy because this not C99 mode
	for(/*int */i=0;i<MAX_CACHE_OBJECT;i++) 
	{
		cache[i].buf=cache[i].flag=NULL;
		cache[i].timeFlag=0;
	}
}

static int eviction()//eviction using LRU
{
	int Min=timeFlag+1,id;
	int i;//make gcc happy because this not C99 mode
	for(/*int */i=0;i<MAX_CACHE_OBJECT;i++)
		if (cache[i].timeFlag>0&&cache[i].timeFlag<Min)
		{
			Min=cache[i].timeFlag;
			id=i;
		}
	now-=strlen(cache[id].buf)+1;
	free(cache[id].buf);
	free(cache[id].flag);
	cache[id].buf=cache[id].flag=NULL;
	cache[id].timeFlag=0;
	return id;
}

void addCache(char*host,char*port,char*path,char*buffer,int size)
//add the pair(host,port,path) and buffer into the cache
{
	int l=strlen(host)+strlen(port)+strlen(path);
	while (size+now+1>MAX_CACHE_SIZE) eviction();
	size+=now+1;
	int id=0,flag=0;
	for(;id<MAX_CACHE_OBJECT;id++)
		if (!cache[id].timeFlag)
		{
			flag=1;
			break;
		}
	if (!flag) id=eviction();
	cache[id].buf=malloc(size+1);
	int i;//make gcc happy because this not C99 mode
	for(/*int */i=0;i<size;i++) cache[id].buf[i]=buffer[i];
	cache[id].buf[size]='\0';
	cache[id].flag=malloc(l+1);
	sprintf(cache[id].flag,"%s%s%s",host,port,path);
	cache[id].flag[l]='\0';
	cache[id].timeFlag=++timeFlag;
}

int isCache(char*host,char*port,char*path,int fd)
//check if the pair(host,port,path) in the cache
{
	char buf[MAXLINE];
	int l=strlen(host)+strlen(port)+strlen(path);
	int i;//make gcc happy because this not C99 mode
	sprintf(buf,"%s%s%s",host,port,path);
	buf[l]='\0';
	for(/*int */i=0;i<MAX_CACHE_OBJECT;i++)
		if (cache[i].timeFlag&&strcmp(buf,cache[i].flag)==0)
		{
			Rio_writen(fd,cache[i].buf,strlen(cache[i].buf));
			return 1;
		}
	return 0;
}