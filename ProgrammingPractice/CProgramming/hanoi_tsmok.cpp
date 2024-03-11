#include<stdio.h>

void hanoi(int num, char from, char by, char to);

int main()
{
	
	hanoi(10, 'A', 'B', 'C');
	return 0;
}

void hanoi(int num, char from, char by, char to)
{
	if(num==0){
		return;
	}
		
	hanoi(num-1, from, to , by);
	printf("%d�� %c���� %c�� �̵�\n", num, from, to);
	hanoi(num-1, by, from, to );
}
