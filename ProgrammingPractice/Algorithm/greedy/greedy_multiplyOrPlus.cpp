#include<iostream>
#include<string>

using namespace std;

int main(){
	
	string input = "";
	int output = 0;
	cin >> input;
	
	//값은 두개씩 비교한다. 
	//두 수중 0이 있거나 1이 있으면 무조건 더해라
	//그개 아니면 곱해라
	//문자- 48 = 숫자 
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

