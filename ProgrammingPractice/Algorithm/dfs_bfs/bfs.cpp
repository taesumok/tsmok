#include<queue>
#include<iostream>

using namespace std;


void bfs(vector<int> graph[] , int visit[], int x){
	
	//graph�� ���� queue ���� 
	queue<int> q_graph;
	
	//queue�� push 
	q_graph.push(x);
	
	//ó�� start���� �ٳన check 
	visit[x] = 1;
	
	//queue�� ��� ��ﶧ�� 
	while(!q_graph.empty()){
		int parent = q_graph.front();
		cout << parent << ' ';
		q_graph.pop();
		for(int i = 0 ; i < graph[parent].size(); ++i){
			int child = graph[parent][i];
			if(visit[child] == 0){
				visit[child] = 1;
				q_graph.push(child);
			}	
		}
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
	
	bfs(graph, visit, 1);
	
		
}
