#include<stdio.h>

int main(int argc, char* argv[]){
	
	int arr[3][3] = {{1,2,3},{1,2,3},{4,5,6}};

	
	printf("%d\n", sizeof(&(arr[0]))/sizeof(int));
	printf("%d\n", sizeof(arr[0])/sizeof(int));
	
	
	return 0;
	
	
}
