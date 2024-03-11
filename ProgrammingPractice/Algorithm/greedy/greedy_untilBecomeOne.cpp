#include<iostream>

using namespace std;

int main(){
	
	int n;
	int k;
	int cnt;
	
	cin >> n >> k ;
	
	while(n!=1){
		printf("%d %d\n", n,k);
		if(n%k == 0){
			n/=k;
		}
		else{
			n--;	
		}
		cnt++;
	}
	
	printf("answer : %d\n", cnt);
	
}

