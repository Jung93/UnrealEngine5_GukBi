#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//น้มุ 11659

	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	int vecSize = 0;
	int total = 0;
	long long num = 0;
	long long oldNum = 0;

	cin >> vecSize >> total;
	vector<long long> vec;

	vec.reserve(vecSize);
	vec.push_back(0);

	for (int i = 0; i < vecSize; i++)
	{
		oldNum += num;
		cin >> num;
		vec.push_back(oldNum + num);
	}

	for (int i = 0; i < total; i++)
	{
		int x = 0;
		int y = 0;

		cin >> x >> y;
		cout << vec[y] - vec[x - 1] << '\n';
	}

	return 0;
}