#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


//우선순위 큐
//1. 완전이진트리
//2. 힙 이론
class PriorityQueue
{
public:

	void push(int value)
	{
		v.push_back(value);

		int now = v.size() - 1;
		while (true)
		{
			if (now <= 0)
				break;

			int parent = (now - 1) / 2;

			if (v[parent] >= v[now])
				break;

			swap(v[parent], v[now]);
			now = parent;
		}
	}

	int top()
	{
		return v[0];
	}

	void pop()
	{
		swap(v[0], v[v.size() - 1]);
		v.pop_back();

		int now = 0;

		while (true)
		{
			if (now >= v.size() - 1)
				break;

			int left = now * 2 + 1;
			int right = now * 2 + 2;
		
			if (left >= v.size())
				break;

			if (right <= v.size() - 1)
			{
				int bigIndex = 0;
				if (v[left] > v[right])
				{
					bigIndex = left;
				}
				else
				{
					bigIndex = right;
				}

				if (v[bigIndex] > v[now])
				{
					swap(v[bigIndex], v[now]);
					now = bigIndex;
				}
				else
				{
					break;
				}

			}
			else
			{
				if (v[left] > v[now])
				{
					swap(v[left], v[now]);
					now = left;
				}
				else
				{
					break;
				}
			}
		}
	}

	bool empty()
	{
		return v.empty();
	}

private:
	vector<int> v;
};


int main()
{
	PriorityQueue pq;
	pq.push(100);
	pq.push(80);
	pq.push(70);
	pq.push(50);
	pq.push(75);

	while (true)
	{
		if (pq.empty())
			break;

		int top = pq.top();
		cout << top << endl;
		pq.pop();
	}

	return 0;

}