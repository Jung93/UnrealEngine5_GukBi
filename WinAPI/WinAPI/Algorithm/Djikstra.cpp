#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<vector<int>> adjacent;
vector<int> parent;
vector<int> best;


struct Vertex
{
	Vertex() {}
	Vertex(int num, int cost) : vertexNum(num), cost(cost) {}

	int vertexNum = 0;
	int cost = 0;//가중치 개복치 참치 꽁치 날치 한치 숙취 발자취

	
	bool operator<(const Vertex& v) const
	{
		if (cost < v.cost)
			return true;
		return false;
	}

	bool operator>(const Vertex& v) const
	{
		if (cost > v.cost)
			return true;
		return false;
	}
};

void CreateGraph()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));
	parent = vector<int>(7, -1);


	adjacent[0][0] = 0;
	adjacent[0][1] = 1;
	adjacent[0][2] = 10;
	adjacent[0][3] = 5;

	adjacent[1][0] = 1;
	adjacent[1][1] = 0;
	adjacent[1][2] = 5;
	adjacent[1][4] = 5;

	adjacent[2][0] = 10;
	adjacent[2][1] = 5;
	adjacent[2][2] = 0;
	adjacent[2][5] = 3;
	adjacent[2][6] = 8;

	adjacent[3][0] = 5;
	adjacent[3][3] = 0;
	adjacent[3][6] = 10;

	adjacent[4][1] = 5;
	adjacent[4][4] = 0;

	adjacent[5][2] = 3;
	adjacent[5][5] = 0;

	adjacent[6][2] = 8;
	adjacent[6][3] = 10;
	adjacent[6][6] = 0;

}


//DBF에서 가중치가 추가된 개념
void Djikstra(int start)
{
	best = vector<int>(adjacent.size(), INT_MAX);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	Vertex startV = Vertex(start, 0);
	best[start] = 0;
	pq.push(startV);

	while (true)
	{
		if (pq.empty())
			break;

		Vertex hereV = pq.top();
		pq.pop();


		if (best[hereV.vertexNum] < hereV.cost)
			continue;

		for (int there = 0; there < adjacent.size(); there++)
		{
			if (hereV.vertexNum == there)
				continue;

			if (adjacent[hereV.vertexNum][there] == -1)
				continue;

			int thereCost = hereV.cost + adjacent[hereV.vertexNum][there];

			//이전 발견한 best가 더 작을 경우
			if (thereCost >= best[there])
				continue;

			Vertex thereV(there, thereCost);
			pq.push(thereV);
			best[there] = thereCost;
			parent[there] = hereV.vertexNum;

		}


	}



}

int main()
{

	CreateGraph();
	Djikstra(0);

	return 0;
}