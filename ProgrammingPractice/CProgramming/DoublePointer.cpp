#include<stdio.h>

#define WIDTH 3

void showArr(int (*)[WIDTH], int ) ;



int main(){
	int arr[2][WIDTH] = { 1,2,3,4,5,6 };
	
	showArr(arr, sizeof(arr)/sizeof(arr[0]));
}
void showArr(int (*arr)[WIDTH], int rowNum)
{
	int i,j;
	for(i = 0; i < rowNum; ++i){
		for(j = 0 ; j < WIDTH ; ++j){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
		
	}
}
