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
	
	//�ִ��� ���� �׷����� �������� ���̸� ª�� �ɰ��� �ȴ�.
	//���� ������ �����Ͽ� ª�� ��� �׷��� ���°��� ���� ���� �׷��� ���� �� �ִ�.
	
	 
	cout << answer << endl;
	
	
}

