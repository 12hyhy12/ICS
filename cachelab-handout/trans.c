//Zhang Yuhao
//1500012703
/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"
#include "contracts.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. The REQUIRES and ENSURES from 15-122 are included
 *     for your convenience. They can be removed if you like.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    REQUIRES(M > 0);
    REQUIRES(N > 0);

	int i,j;
	
	if (N==M&&N==32)
	{
		int t[8],x;
		for(x=0;x<M;x+=8)
		{
			for(i=0;i<N;i++)
			{
				for(j=x+7;j>=x;j--) t[j-x]=A[i][j];
				for(j=x+7;j>=x;j--) B[j][i]=t[j-x];
			}
		}
	}
	else if (N==M)
	{
		/*A[a-b][c-d]
		B[c-d][a-b]
		-------------------
		A[a][c-d] M[c-d]<=8
		B[c-d][a] M[a-b]<=16
		A[a+1][c-d]
		B[c-d][a+1]
		
		*/
		int x,l;
		for(x=0;x<M;x+=8)
		{
			for(i=0;i<N;i+=8)
				if (i!=x)
				{
					int st;
					for(st=0;st==x||st==i;st+=8);
					for(l=0;l<4;l++)
					{
						for(j=0;j<4;j++) B[x+j][i+l]=A[i+l][x+j];
						for(j=4;j<8;j++) B[st+j][st+l]=A[i+l][x+j];
					}
					for(l=4;l<8;l++)
					{
						for(j=4;j<8;j++) B[st+j][st+l]=A[i+l][x+j];
						for(j=0;j<4;j++) B[x+j][i+l]=A[i+l][x+j];
					}
					for(l=4;l<8;l++)
						for(j=0;j<8;j++) B[x+l][i+j]=B[st+l][st+j];
				}
		}
		int t[4];
		for(x=0;x<M;x+=4)
		{
			for(i=x/8*8;i<x/8*8+8;i++)
			{
				for(j=x+3;j>=x;j--) t[j-x]=A[i][j];
				for(j=x+3;j>=x;j--) B[j][i]=t[j-x];
			}
		}
		
	}
	else
	{
		int t1,t2,tmp,x,y;
		for (i = 0; i < N; i+=21)
		    for (j = 0; j < M; j+=23)
		    {
		    	t1=i+21;t2=j+23;
		    	if (t1>N) t1=N;
		    	if (t2>M) t2=M;
		    	for (x=i;x<t1;x++)
		    		for(y=j;y<t2;y++)
		    		{
		    			tmp=A[x][y];
		    			B[y][x]=tmp;
		    		}
			}
	}
    ENSURES(is_transpose(M, N, A, B));
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

