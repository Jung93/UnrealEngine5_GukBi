#include <iostream>
#include <vector>

using namespace std;

int cache[1001];
int step = 0;

int LIS(int n, vector<int>& v)
{
	if (step >= 3)
		return 0;

	if (n <= 0)
		return 0;

	int& ref = cache[n];

	if (ref != -1)
		return ref;

	ref = v[n];
	for (int prev = n - 1; prev >= 0; prev--)
	{
		step++;
		if (v[n] >= v[prev])
			ref = std::max(ref, LIS(prev, v) + v[n]);
	}

	return ref;
}

int main()
{
	int vecSize = 0;
	int num = 0;
	int answer = 0;

	cin >> vecSize;
	vector<int> vec;

	for (int i = 0; i < vecSize; i++)
	{
		cin >> num;
		vec.push_back(num);
	}

	for (int i = 0; i < 1001; i++)
	{
		cache[i] = -1;
	}

	answer += vec[vec.size() - 1];


	for (int i = 0; i < vec.size(); i++)
	{
		answer = std::max(answer, LIS(i, vec));
	}


	cout << answer;

	return 0;
}