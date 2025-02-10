#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct User
{
	int guildId = 0;


};

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < 1000; i++)
	{
		users.push_back({ i });
	}

	users[555].guildId = users[1].guildId;

	// guildId가 2인 유저를 1길드에 통합 -> N만큼의 시간 복잡도 
	for (auto& user : users)
	{
		if (user.guildId == 2)
			user.guildId = 1;
	}

	NaiveDisJointSet set(1000);
	set.Merge(555, 1);

	set.Merge(2, 1);

}

class NaiveDisJointSet
{
public:
	NaiveDisJointSet(int n)
	{
		_parent = vector<int>(n, 0);
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
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

		_parent[uLeader] = vLeader;

	}

private:
	vector<int> _parent;

};

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


int main()
{
	GuildSystem();

	return 0;
}