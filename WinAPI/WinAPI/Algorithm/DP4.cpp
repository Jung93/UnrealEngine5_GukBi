#include <iostream>
#include <vector>

using namespace std;

//LIS (부분 증가 수열)의 합
//{1 , 10, 11, 15, 30} 증가수열
//{10 , 5, 6 ,7 ,9} 
//-> 5 6 9 부분 증가수열


int LIS(vector<int> v) //Longest Increasing Sequence.
{
	vector<int> temp;

	for (int y = 0; y < v.size(); y++)
	{
		int result = 0;
		int num = v[y];
		for (int i = y; i < v.size(); i++)
		{
			if (num <= v[i])
			{
				result += v[i];
				num = v[i];
			}
			else
			{
				continue;
			}
		}

		temp.push_back(result);
	}
	return *max_element(temp.begin(), temp.end());
}



int cache[1001];

int LIS(int n, vector<int>& v)
{

	if (n == v.size() - 1)
		return v[n];

	int& ref = cache[n];

	if (ref != -1)
		return ref;

	ref = v[n];
	for (int next = n + 1; next < v.size(); next++)
	{
		if (v[n] <= v[next])
			ref = std::max(ref, LIS(next, v) + v[n]);
	}

	return ref;
}

int main()
{
	//vector<int> v = { 10 , 5, 6 ,7 ,9 }; //27
	//vector<int> v = { 10, 7, 5, 3 }; //10
	//vector<int> v = { 15, 30, 10, 17, 50 }; //95
	//vector<int> v = { 1, 10, 11, 15, 30 }; //67
	//vector<int> v = { 5,4,3,2,1 }; //5
	vector<int> v = { 1,2,3,4,5 }; //15

	//for (int i = 0; i < 1001; i++)
	//{
	//	cache[i] = -1;
	//}
	//int answer = 0;
	//for (int i = 0; i < v.size(); i++)
	//{
	//	answer = std::max(answer, LIS(i, v));
	//}

	//cout << answer;

	cout << LIS(v);

	return 0;
}
