#include <iostream>
#include <vector>

using namespace std;

//+1 +2 +3

//1老 锭 1
//1

//2老 锭 2
//1 1
//2

//3老 锭 4
//1 1 1
//1 2
//2 1
//3

//4老 嫐 7
//1 1 1 1
//1 1 2
//1 2 1
//1 3
//2 1 1
//2 2
//3 1

//5老 锭 13
//1 1 1 1 1
//1 1 1 2
//1 1 2 1
//1 2 1 1
//1 1 3
//1 2 2
//1 3 1
//2 1 1 1
//2 2 1
//2 1 2
//2 3
//3 1 1
//3 2


//6老 锭 24
//1 1 1 1 1 1
//1 1 1 1 2
//1 1 1 2 1
//1 1 2 1 1
//1 2 1 1 1
//1 1 1 3
//1 1 3 1
//1 3 1 1
//1 1 2 2
//1 2 1 2
//1 2 2 1
//2 1 1 1 1
//2 2 1 1
//2 1 2 1
//2 1 1 2
//2 2 2
//3 3
//3 1 1 1
//1 2 3
//1 3 2
//2 1 3
//2 3 1
//3 1 2
//3 2 1


vector<int> cache = vector<int>(1001, -1);
int Ganghwa(int n)
{
	if (n == 1 || n == 2)
		return n;
	if (n == 3)
		return 4;

	int& ref = cache[n];
	if (ref != -1)
		return ref;

	return ref = Ganghwa(n - 1) + Ganghwa(n - 2) + Ganghwa(n - 3);
}

int main()
{
	cout << Ganghwa(103);
	return 0;
}