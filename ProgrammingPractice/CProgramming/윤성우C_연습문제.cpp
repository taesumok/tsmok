#include<stdio.h>
#include<stdlib.h>


int main()
{
	

	/*
	[0][0] => [0][1] => [0][2] => [0][3] => [1][3] => [2][3] => [3][3] => [3][2] => [3][1] => [3][0] => [2][0] => [1][0] => [1][1] => [1][2] => 
	                                
	*/
	int length = 0;
	int num = 1;
	int curRow= 0;	
	int curColmn = 0;
	int turn = 1;
	
	
	printf("사각형 한 변의 길이를 입력하시오 : ");
	scanf("%d", &length);
	int arr[length][length];
	
	for(int i = 0 ; i < length; ++i){
		for(int j = 0 ; j < length; ++j)
			arr[i][j] = 0;
	}
	
	int endIdx = length;
	while(num<=length*length){
		
		for(int i = 0 ; i < endIdx ; ++i){
			arr[curRow][curColmn] = num;
			num++;	
			if(i < endIdx-1)
				curColmn+=turn;
		}
		curRow+=turn;
		endIdx--;
	
		for(int i = 0 ; i < endIdx; ++i){
			arr[curRow][curColmn] = num;
			num++;
			if(i < endIdx-1)
				curRow+=turn;	
		}
		turn*=-1;
		curColmn+=turn;
	}
	
	
	for(int i = 0 ; i < length ; ++i){
		for(int j = 0; j < length ; ++j){
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
		

	
	
	
	
	
	
}

	

