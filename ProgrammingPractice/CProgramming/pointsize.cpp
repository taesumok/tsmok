#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

void f_test(char* arr);

int main()
{
	
	char arr[10];
	
	memset(arr, 0x00, sizeof(arr));
	printf("arr size[%d]\n", sizeof(&arr[0]));	
	f_test(arr);
	return 0;
	
}

void f_test(char * arr)
{
	printf("arr size in f_test[%d]\n", sizeof(arr));
}
