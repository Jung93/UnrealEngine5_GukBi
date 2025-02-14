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
		for (int i = 0; i < v.size(); i++)
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

int main()
{
	vector<int> v = { 10 , 5, 6 ,7 ,9 };

	cout << LIS(v) << endl;

	return 0;
}
