#include <iostream>
#include <stack>
#include <queue>
#include <list>

// stack, queue
//stack : 선입후출 FILO
//queue : 선입선출 FIFO

using namespace std;

template <typename T>
class Queue
{
public:

	void push(T value)
	{
		_data.push_back(value);
	}

	T front()
	{
		return _data.front();
	}

	void pop()
	{
		return _data.pop_front();
	}

	bool empty()
	{
		return _data.empty();
	}

private:
	list<T> _data;
};


int main()
{
	//stack<int> s;
	//queue<int> q;
	Queue<int> q;

	q.push(1);
	q.push(5);
	q.push(30);
	q.push(2);
	q.push(452);

	while (true)
	{
		if (q.empty())
			break;

		cout << q.front() << endl;
		q.pop();
	}


	return 0;

}

