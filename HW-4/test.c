void bubble_a(long *data,long count)
{
	long i,last;
	for(last=count-1;last>0;last--)
	{
		long *a=data,*b;
		for(i=0;i<last;i++,a++)
		{
			b=a+1;
			if (*b<*a)
			{
				long t=*b;
				*b=*a;
				*a=t;
			}
		}
	}
}
