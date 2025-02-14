#include <iostream>
#include <vector>

using namespace std;

//а╤гу
vector<vector<int>> cache = vector<vector<int>>(31, vector<int>(31,-1));
int Combination(int n, int r)
{

	if (n == r || r == 0)
		return 1;

	if (r == 1)
		return n;

	int& ref = cache[n][r];
	if (ref != -1)
		return ref;

	return ref = Combination(n - 1, r) + Combination(n - 1, r - 1);
}


int main()
{
	cout << Combination(30, 15);


	return 0;
}