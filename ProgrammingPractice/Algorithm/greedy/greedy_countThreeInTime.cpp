#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	int N=0;
	
	//00 ~ 59�� 3�� �� ��� => 10�� ���� ���� 3�̰ų� �������� 3�� ��� 
	//00 ~ 59�� 
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

