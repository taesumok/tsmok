#include<stdio.h>

int binarySearch(char data[] , char target, int first, int second){
	static int cnt = 0;
	if(second<first)
		return -1;
	
	int cur = (first+second)/2;
	cnt++;
	if(data[cur] == target){
		printf("[%d]번째 문자열 %c를 %d번만에 찾았습니다\n", cur, data[cur], cnt);
		return cur;
	}
	else if(data[cur] > target)
		binarySearch(data, target, first, cur-1);
	else if(data[cur] < target)
		binarySearch(data,target, cur+1 , second);
}


int main() {
	char target = 0;
	char data[7] = { 'A','B','C','D','E','G','H' };

	printf("찾을 문자 : ");
	scanf("%c", &target);
	if (binarySearch(data, target, 0, 6) == -1)
		printf("%c 문자를 찾을 수 없습니다.\n", target);
}