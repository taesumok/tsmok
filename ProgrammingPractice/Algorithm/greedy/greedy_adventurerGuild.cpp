#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(int a, int b){
	return a<b;
}

int main(){
	
	int N = 0;
	int X = 0;
	int answer=0;
	
	vector<int> adventurer;
	
	cin >> N;
	for(int i = 0; i < N; ++i){
		cin >> X;
		adventurer.push_back(X);	
	}
	
	sort(adventurer.begin(), adventurer.end(), compare);
	
	int cnt = 0;
	for(int i = 0 ; i <adventurer.size(); ++i){
		cnt++;
		if(cnt>=adventurer[i]){
			answer++;
			cnt=0;
		}
	}
	
	//최대한 많은 그룹수라는 것은가장 길이를 짧게 쪼개야 된다.
	//작은 값부터 정렬하여 짧게 끊어서 그룹을 짓는것이 가장 많은 그룹을 만들 수 있다.
	
	 
	cout << answer << endl;
	
	
}

