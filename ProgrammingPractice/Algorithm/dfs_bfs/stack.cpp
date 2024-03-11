#include<stack>
#include<iostream>

using namespace std;

int main(){
	stack<int> stc;
	for(int i = 0; i < 5;++i)
		stc.push(i);
	
	
	while(!stc.empty()){
		cout << stc.top() << " ";
		stc.pop();
	}
	
		
	
}
