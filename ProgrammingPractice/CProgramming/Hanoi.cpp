#include<stdio.h>

int hanoi(int num, char start, char by, char end){
	
	if(num == 1){
		printf("%d벽돌을 %c에서 %c로 이동\n", num, start, end);
		return 0;
	}
	hanoi(num-1, start, end, by);
	printf("%d벽돌을 %c에서 %c로 이동\n", num, start, end);
	hanoi(num-1, by, start, end);
}
// 1
// 2  
// a b c 



int main()
{ 
	hanoi(4, 'a', 'b', 'c');
	
}
