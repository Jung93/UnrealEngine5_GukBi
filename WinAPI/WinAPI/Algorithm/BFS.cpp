#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//DFS, BFS

vector<vector<bool>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));
	discovered = vector<bool>(7, false);
	parent = vector<int>(7, -1);


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

	int a = 1;
}

void BFS(int start)
{
	discovered[start] = true;
	parent[start] = start;
	queue<int> q;
	q.push(start);

	while (true)
	{
		if (q.empty())
			break;

		int here = q.front();
		q.pop();
		cout << "Here : " << here << endl;

		for (int there = 0; there < adjacent.size(); there++)
		{
			//현재 here와 there가 같나
			if (here == there)
				continue;

			//here와 there가 인접 안되어있나
			if (adjacent[here][there] == false)
				continue;

			//방문이 되어있나
			if (discovered[there] == true)
				continue;


			q.push(there);
			discovered[there] = true;
			parent[there] = here;
		}

	}


}

int main()
{

	CreateGraph();

	if (adjacent[0][2] && adjacent[2][0])
		cout << "연결되어있다" << endl;

	BFS(0);

	int distance = 0;
	int tempParent = 6;
	while (true)
	{
		tempParent = parent[tempParent];
		distance++;

		if (tempParent == parent[tempParent])
			break;

	}

	cout << distance << endl;

	return 0;

}