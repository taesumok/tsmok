#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	int N=0;
	
	//00 ~ 59초 3이 들어갈 경우 => 10을 나눈 몫이 3이거나 나머지가 3일 경우 
	//00 ~ 59분 
	int cnt=0;
	
	cin >> N;
	
	for(int i = 0 ; i <= N ; ++i){
		for(int j = 0 ; j <= 59 ; ++j){
			for(int k = 0; k <= 59 ; ++k){
				if(i/10 == 3 || i%10 == 3 || j/10 == 3 || j%10 == 3 || k/10 ==3 || k%10 == 3) cnt++;
			}
		}
	}
				
			
		
	
	cout << cnt << endl;
	
	
	
	
}

