#include<iostream>
#include<string>

using namespace std;

int main(){
	
	string input = "";
	int output = 0;
	cin >> input;
	
	//���� �ΰ��� ���Ѵ�. 
	//�� ���� 0�� �ְų� 1�� ������ ������ ���ض�
	//�װ� �ƴϸ� ���ض�
	//����- 48 = ���� 
	output = input[0]-48;
	for(int i = 1; i < input.size(); ++i){
		if(input[i-1]-48 < 2 || input[i]-48 < 2){
			output += (input[i]-48);
		}
		else{
			output *= (input[i]-48);
		}
	} 
	cout << output << endl;
	
}

