#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	
	string input="";
	
	cin >> input;
	
	string output="";
	int sum=0;
	
	sort(input.begin(),input.end());
	
	for(int i = 0 ; i < input.length(); ++i){
		if(input[i] >= 'a' && input[i] <= 'z' || input[i] >= 'A' && input[i] <= 'Z')
			output+=input[i];
		else{
			sum+=(input[i]-'0');
		}	
	}
	if(sum!=0) 
		cout << output << sum << endl;
	else
		cout << output << endl;	
}

