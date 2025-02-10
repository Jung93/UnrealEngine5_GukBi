#pragma once

#include <vector>
//#include <algorithm>

using namespace std;

class DisJoinSet
{

public:
	DisJoinSet(int n)
	{
		_parent = vector<int>(n, 0);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}

		_rank = vector<int>(n, 1);
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
			swap(uLeader, vLeader);

		//vLeader의 랭크가 항상 크거나 같다
		_parent[uLeader] = vLeader;

		//같은 랭크를 가졌으면 1 증가
		if (_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;

};