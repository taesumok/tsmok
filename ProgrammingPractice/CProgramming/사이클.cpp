#include<stdio.h>

int main()
{
	int n = 0;
	int old_n = 0;
	int cnt = 0;
	
	printf("N�� �Է��Ͻÿ� : ");
	scanf("%d", &n);
	old_n = n;
	
	do{
		n = ((n%10)*10) + (((n/10)+(n%10))%10);
		cnt++;
		printf("N[%d] : %d\n", cnt, n); 
	}while(n!=old_n);
	printf("N�� ����Ŭ�� %d �Դϴ�\n", cnt);
}
