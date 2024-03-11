#include<queue>
#include<iostream>

using namespace std;

int main(){
	queue<int> que;
	
	for(int i = 0 ; i < 5; ++i){
		que.push(i);
	}	
	while(!que.empty()){
		cout << que.front() << " ";
		que.pop();
	}
}
