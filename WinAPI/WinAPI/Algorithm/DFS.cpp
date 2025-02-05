#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//DFS

vector<vector<bool>> adjacent;
vector<bool> visited;

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));
	visited = vector<bool>(7, false);

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][3] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][4] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][5] = true;
	adjacent[2][6] = true;

	adjacent[3][0] = true;
	adjacent[3][3] = true;

	adjacent[4][1] = true;
	adjacent[4][4] = true;

	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][2] = true;
	adjacent[6][6] = true;

}

void DFS(int here)
{
	visited[here] = true;
	cout << here << endl;

	for (int there = 0; there < adjacent.size(); there++)
	{
		if (here == there)
			continue;

		if (visited[there] == true)
			continue;

		if (adjacent[here][there] == false)
			continue;

		DFS(there);

	}

}

int main()
{

	CreateGraph();
	DFS(6);


	return 0;

}