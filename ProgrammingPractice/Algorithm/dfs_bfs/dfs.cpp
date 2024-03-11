#include<queue>
#include<iostream>

using namespace std;


void dfs(vector<int> graph[] , int visit[], int x){
	if(visit[x] == 1){
		return;
	}
	visit[x] = 1;	
	cout << x << ' ';
	
	for(int i = 0 ; i < graph[x].size(); ++i){
		if(visit[graph[x][i]]==0)
			dfs(graph, visit, graph[x][i]);
	}
} 

int main()
{
	int visit[9] = {0};
	vector<int> graph[9];
	
	graph[1].push_back(2);
	graph[2].push_back(1);
	
	graph[1].push_back(3);
	graph[3].push_back(1);
	
	graph[2].push_back(4);
	graph[4].push_back(2);
	
	graph[2].push_back(5);
	graph[5].push_back(2);
	
	
	graph[3].push_back(6);
	graph[6].push_back(3);
	
	graph[3].push_back(7);
	graph[7].push_back(3);
	
	graph[3].push_back(8);
	graph[8].push_back(3);
	
	dfs(graph, visit, 1);
	
		
}
