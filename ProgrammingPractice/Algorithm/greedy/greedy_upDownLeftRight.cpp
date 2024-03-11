#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	int N=0;
	string direction;
	int x = 1;
	int y = 1;
	cin >> N;
	cin.ignore();
	getline(cin, direction);
	
	cout << "[" << y << "," << x << "]" << endl;  
	
	for(int i = 0; i < direction.length(); ++i){
		if(direction[i] == ' '){
			continue;
		}
		else{
			switch(direction[i]){
				case 'L':
					if(x>1) x--;
					break;
				case 'R':
					if(x<N) x++;
					break;
				case 'U':
					if(y>1) y--;
					break;
				case 'D':
					if(y<N) y++;
					break;
				default:
					break;
			}	
		}
	}
	
	cout << "[" << y << "," << x << "]" << endl;  
	
	
	
	
}

