#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "BST.h"

using namespace std;

//BST
//이진탐색트리



//

class Player
{
public:
	bool operator<(const Player& other) const
	{
		return hp < other.hp;
	}

	bool operator==(const Player& other) const
	{
		return hp == other.hp;
	}

	int hp;
	int atk;

};

int main()
{
	BinarySearchTree bst;
	bst.Insert(100);
	bst.Insert(50);
	bst.Insert(25);
	bst.Insert(75);
	bst.Insert(150);
	bst.Insert(110);
	bst.Insert(200);
	bst.Insert(99);

	map<string, int> m;
	m["abc"] = 1;

	auto iter = m.insert(make_pair<string, int>("def", 2));

	cout << m["asdasdasd"] << endl;

	

	//for (auto p : m)
	//{
	//	cout << p.first << "..." << p.second << endl;
	//}

	//map<Player, int> pm;
	//pm[{10, 5}] = 5;

	return 0;
}