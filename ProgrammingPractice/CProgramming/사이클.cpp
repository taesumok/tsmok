#include<stdio.h>

int main()
{
	int n = 0;
	int old_n = 0;
	int cnt = 0;
	
	printf("N을 입력하시오 : ");
	scanf("%d", &n);
	old_n = n;
	
	do{
		n = ((n%10)*10) + (((n/10)+(n%10))%10);
		cnt++;
		printf("N[%d] : %d\n", cnt, n); 
	}while(n!=old_n);
	printf("N의 사이클은 %d 입니다\n", cnt);
}
