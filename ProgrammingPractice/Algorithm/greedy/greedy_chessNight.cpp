#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	
	int dx[8] = {-2,-1,1,2,-2,-1,1,2 };
	int dy[8] = {-1,-2,2,1,1,2,-2,-1};
	string input;
	int cnt=0;
	cin >> input;
	
	int x = (int)input[0]-'a'+1;		//알파벳(소문자)를 숫자로 
	int y = input[1]-'0';	//숫자문자를 숫자로  
	int nx,ny = 0;
	
	for(int i = 0 ; i < 8 ; ++i){
		nx = x+dx[i];
		ny = y+dy[i];
		
		if(nx>=1 && nx <= 8 && ny>=1 && ny<=8)
			cnt++;
	}
	cout << cnt << endl;
	
	
}

