#include<stdio.h>

void BubbleSort(int*, int);

int main(int argc, char* argv[])
{
	int arr[4] = {3,2,1,4};
	int i=0;
	BubbleSort(arr, sizeof(arr)/sizeof(int));
	
	printf("%d \n", sizeof(arr)/sizeof(int));
	for(i = 0; i < 4; ++i){
		printf("%d ",arr[i]);
	}
	printf("\n");
	
}

void BubbleSort(int* arr, int len)
{
	int i,j=0;
	for(i = 0; i < len-1 ; ++i){
		for(j = 0 ; j < len-1-i; ++j){
			if(arr[j]<arr[j+1]){
			
				int temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	
}
