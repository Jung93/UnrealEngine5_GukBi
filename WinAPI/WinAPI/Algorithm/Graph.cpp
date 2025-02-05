#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//그래프
//Vertex와 edge로 이루어진 자료구조

//DFS, BFS

//인접리스트
vector<vector<int>> adjacent_list;
void CreateGraph_list()
{
	adjacent_list.resize(7);
	adjacent_list[0] = { 0,1,2,3 };
	adjacent_list[1] = { 0,1,4 };
	adjacent_list[2] = { 0,2,5,6 };
	adjacent_list[3] = { 0,3 };
	adjacent_list[4] = { 1,4 };
	adjacent_list[5] = { 2,5 };
	adjacent_list[6] = { 2,6 };

}

vector<vector<bool>> adjacent;
void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

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

int main()
{
	//CreateGraph_list();

	//0과 2가 연결되어있나?
	//auto iter = find(adjacent_list[0].begin(), adjacent_list[0].end(), 2);
	//if (iter != adjacent_list[0].end())
	//	cout << "연결되어있다" << endl;

	CreateGraph();

	if(adjacent[0][2] && adjacent[2][0])
		cout << "연결되어있다" << endl;


	return 0;

}

