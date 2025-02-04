#include <iostream>
#include <stack>
#include <queue>
#include <list>

// stack, queue
//stack : 선입후출 FILO
//queue : 선입선출 FIFO

using namespace std;

template <typename T = int>
class Stack
{
public:

	void push(T value)
	{
		_data.push_front(value);
	}

	T top()
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
	Stack<> s;

	s.push(1);
	s.push(5);
	s.push(30);
	s.push(2);
	s.push(452);

	while (true)
	{
		if (s.empty())
			break;

		cout << s.top() << endl;
		s.pop();
	}


	return 0;

}

