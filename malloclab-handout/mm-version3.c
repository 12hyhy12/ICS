//1500012703
//Zhang Yuhao
/*
 * mm.c
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
# define dbg_printf(...) printf(__VA_ARGS__)
#else
# define dbg_printf(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)

#define INIT_SIZE 2
#define REMAIN_SIZE 6
#define USED_SIZE 2
#define is_used(node) ((*node)&1)
#define MAX_UINT ((long long)UINT_MAX+1)
#define PARA1 40
#define PARA2 200
#define max(x,y) ((x>y)?x:y)
#define min(x,y) ((x<y)?x:y)
//#define NODE_SIZE 9
//#define MAX_UINT (1LL<<32)
//#define left_spare(node) (*(MAX_UNINT*(*node)+*(node+1)+7))
//#define right_spare(node) (*(MAX_UNINT*(*(node+2))+*(node+3)+7))
//#define pointer(node) (MAX_UINT*(*node)+*(node+1))
static unsigned int *pointer(unsigned int*node) 
{return (unsigned int *)((unsigned long long)MAX_UINT*(*node)+(*(node+1)));}
//#define pre(node) pointer(node+1)
static unsigned int *pre(unsigned int*node) {return pointer(node+1);}
//#define suc(node) pointer(node+3)
static unsigned int *suc(unsigned int*node) {return pointer(node+3);}
#define free_head ((unsigned int*)mem_heap_lo())
#define free_tail pre(free_head)
#define max_in_head (*(free_head+5))
//#define use_head mem_heap_lo()+REMAIN_SIZE
//#define use_tail pre(ues_head)

/*
 * Initialize: return -1 on error, 0 on success.
 */
 
 /*********************************/
 //static int call=0,this_call=0;
 /*********************************/
 
/*static void init_node(unsigned int *node,unsigned int size)
{
	*(node)=0U;		//left node
	*(++node)=0U;
	*(++node)=0U;	//right node
	*(++node)=0U;
	*(node+1)=size;	//size
	*(node+2)=size;	//left spare size
	*(node+3)=size; //right spare size
	*(node+4)=size; //segment spare size
	*(node+5)=0;	//flag
}*/


/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
static int in_heap(const void *p) {
    return p <= mem_heap_hi() && p >= mem_heap_lo();
}


static unsigned int getsize(unsigned int* p){return (*p)-is_used(p);}

static void set_pointer(unsigned int *p,unsigned int *q)
{
	unsigned long long x=(unsigned long long)q;
	*p=(unsigned int)(x/MAX_UINT);
	*(p+1)=(unsigned int)(x&(MAX_UINT-1));
}

static void init_node(unsigned int*p,unsigned int size,unsigned int*pre,unsigned int*suc)
{
	*p=size;
	set_pointer(p+1,pre);
	set_pointer(p+3,suc);
}

int mm_init(void) {
	//void *root=mem_sbrk(INIT_SIZE*NODE_SIZE*8);
	//init_node(root,(unsigned int)4294967296U);
	unsigned int *p=mem_sbrk(INIT_SIZE*REMAIN_SIZE*4);
	
	init_node(p,REMAIN_SIZE*4,p+REMAIN_SIZE,p+REMAIN_SIZE);	
	p=p+REMAIN_SIZE;
	init_node(p,REMAIN_SIZE*4,p-REMAIN_SIZE,p-REMAIN_SIZE);
	
	max_in_head=0;

    return 0;
}

static void delete_list(unsigned int*p)
{
	if (getsize(p)<REMAIN_SIZE*4) return;
	unsigned int*Pre=pre(p);
	unsigned int*Suc=suc(p);
	set_pointer(Pre+3,Suc);
	set_pointer(Suc+1,Pre);
}

static void linkto(unsigned int*p)
{
	if (getsize(p)<REMAIN_SIZE*4) return;
	unsigned int* Suc=free_tail;
	unsigned int* Pre=pre(Suc);
	init_node(p,getsize(p),Pre,Suc);
	set_pointer(Suc+1,p);
	set_pointer(Pre+3,p);
	max_in_head=max(max_in_head,getsize(p));
}

static void merge(unsigned int*p)
{
	unsigned int*next=p+getsize(p)/4;
	unsigned int size=*next;
	delete_list(next);
	mm_checkheap(149);
	//printf("%lld %lld\n",(long long)p,(long long)*p);
	/*if (getsize(p)<REMAIN_SIZE*4)
	{
		*p+=size;
		linkto(p);
	}
	else */*p+=size;
	max_in_head=max(max_in_head,getsize(p));
	mm_checkheap(156);
}

static void* find_in_free(unsigned int size)
{
	if (size>max_in_head) return NULL;
	unsigned int *r=free_head,*tail=free_tail,*best;
	best=NULL;
	unsigned int Min=UINT_MAX,t;
	for(r=suc(r);r!=tail;r=suc(r))
	{
		unsigned int*next=r+getsize(r)/4;
		//fprintf(stderr,"%lld\n",(long long)*next);
		while (in_heap(next)&&!is_used(next)) 
		{
			merge(r);
			//fprintf(stderr,"%lld\n",(long long)*r);
			next=r+getsize(r)/4;
		}
		if ((t=getsize(r))>=size) return r;
		/*{
			if (Min>t) 
			{
				Min=t;
				best=r;
			}
		}*/
	}
	if (!best) max_in_head=min(max_in_head,size);
	return best;
}

static void delete(unsigned int*p)
{
	*p-=is_used(p);
	unsigned int*next=p+getsize(p)/4;
	while (in_heap(next)&&!is_used(next)) 
	{
		merge(p);
		next=p+getsize(p)/4;
	}
	linkto(p);
}

void split(unsigned int *p,unsigned int used_size)
{
	unsigned int *freed=p+used_size/4;
	unsigned int remain=getsize(p)-used_size;
	*freed=remain;
	linkto(freed);
	//return freed;
}


/*
 * malloc
 */
void *malloc (size_t size) {
	unsigned int newsize=USED_SIZE*4+ALIGN(size);
	unsigned int *ans=find_in_free(newsize);
	if (ans!=NULL) 
	{
		//fprintf(stderr,"%lld %lld %lld\n",(long long)ans,(long long)getsize(ans),(long long)newsize);
		delete_list(ans);
		if (getsize(ans)>=newsize+REMAIN_SIZE*4+PARA1)
		{
			/*unsigned int*p=*/split(ans,newsize);
			*ans=newsize+1;
		}
		else *ans=(*ans)+1;
		mm_checkheap(169);
		return (void *)(ans+USED_SIZE);
	}
	else
	{
		unsigned int *p=mem_sbrk(newsize);
		*p=newsize+1;
		mm_checkheap(176);
		return (void *)(p+USED_SIZE);
	}
}

/*
 * free
 */
void free (void *ptr) {
	//fprintf(stderr,"%lld\n",(long long)ptr);
	//fprintf(stdout,"%lld\n",(long long)ptr);
	if (ptr==NULL) return;
	unsigned int*Ptr=((unsigned int*)ptr)-USED_SIZE;
	//fprintf(stderr,"%lld\n",(long long)Ptr);
	delete(Ptr);
	mm_checkheap(187);
}

/*
 * realloc - you may want to look at mm-naive.c
 */
void *realloc(void *Oldptr, size_t size) {
	unsigned int *oldptr=(unsigned int*) Oldptr;
	if (oldptr==NULL) return malloc(size);	//if oldptr is NULL, call malloc
	else if (size==0) free(oldptr);	//if size is zero, call free
	else	//otherwise
	{
		oldptr=oldptr-USED_SIZE;
		size=USED_SIZE*4+ALIGN(size);
		long long dlt=(long long)size-getsize(oldptr);
		//printf("%lld\n",dlt);
		if (dlt>0)
		{
			unsigned int *next=oldptr+getsize(oldptr)/4;
			if (in_heap(next)&&!is_used(next)&&(long long)getsize(next)>=dlt)
			{
				//printf("%lld %lld %lld\n",(long long)next,(long long)*next,(long long)dlt);
				//printf("%lld\n",(long long)oldptr);
				delete_list(next);
				if (getsize(next)>=REMAIN_SIZE*4+dlt+PARA1)
				{
					/*unsigned int *p=*/split(next,dlt);
					*oldptr=size+1;
				}
				else *oldptr+=getsize(next);
				mm_checkheap(224);
				return oldptr+USED_SIZE;
			}
			else
			{
				unsigned int *new=malloc(size-USED_SIZE*4);
				new-=USED_SIZE;
				unsigned int len=getsize(oldptr)/4;
				//printf("%d\n",len);
				for(unsigned int i=USED_SIZE;i<len;i++) *(new+i)=*(oldptr+i);
				//printf("yes?\n");
				free(oldptr+USED_SIZE);
				//printf("yes?\n");
				mm_checkheap(234);
				return new+USED_SIZE;
			}
		}
		else
		{
			if (-dlt>=PARA1+REMAIN_SIZE*4)
			{
				/*unsigned int *p=*/split(oldptr,getsize(oldptr)+dlt);
				*oldptr=(*oldptr)+dlt;
			}
			mm_checkheap(246);
			return oldptr+USED_SIZE;
		}
	}
    return NULL;
}

/*
 * calloc - you may want to look at mm-naive.c
 * This function is not tested by mdriver, but it is
 * needed to run the traces.
 */
void *calloc (size_t nmemb, size_t size) {
	unsigned int *ans=malloc(nmemb*size);
	ans-=USED_SIZE;
	unsigned int len=getsize(ans)/4;
	for(unsigned int i=USED_SIZE;i<len;i++) *(ans+i)=0;
	mm_checkheap(263);
    return ans+USED_SIZE;
}


/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
static int aligned(const void *p) {
    return (size_t)ALIGN(p) == (size_t)p;
}

/*
 * mm_checkheap
 */
void mm_checkheap(int lineno) {
	/*fprintf(stdout,"Here in %d:\n",lineno);
	unsigned int *p=free_head;
	int cnt=0;
	for(;in_heap(p);p+=getsize(p)/4)
	{
		cnt++;
		if (getsize(p)==0)
		{
			fprintf(stdout,"error!\n");exit(0);
		}
		if (is_used(p))
		{
			fprintf(stdout,"%lld USED: Size:%lld\n",(long long)p,(long long)*p);
		}
		else
			if (getsize(p)<REMAIN_SIZE*4) fprintf(stdout,"%lld FREE: Size:%lld\n",(long long)p,(long long)*p);
			else 
				fprintf(stdout,"%lld FREE: Size:%lld Pre:%lld Suc:%lld\n",(long long)p,(long long)*p,(long long)pre(p),(long long)suc(p));
	}*/
	//exit(0);
}
