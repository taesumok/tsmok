#include<stdio.h>
#include<Python.h>
int fibo(int a);


int main()
{
	
	printf("%d\n", fibo(10));
	return 0;
		
}

int fibo(int a)
{
	
	if(a==1 || a==2 )
		return 1;
	
	return fibo(a-2) + fibo(a-1);
	
}

