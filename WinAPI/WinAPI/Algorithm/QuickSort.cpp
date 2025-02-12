#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int lowIndex = left + 1;
	int highIndex = right;

	while (true)
	{
		if (lowIndex > highIndex)
			break;

		if (lowIndex <= right && pivot > v[lowIndex])
		{
			lowIndex++;
		}

		if (highIndex >= left && pivot < v[highIndex])
		{
			highIndex--;
		}

		if (lowIndex < highIndex)
		{
			swap(v[lowIndex], v[highIndex]);
		}

	}

	swap(v[highIndex], v[left]);

	return highIndex;
}


void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivotIndex = Partition(v, left, right);

	QuickSort(v, left, pivotIndex - 1);
	QuickSort(v, pivotIndex + 1, right);
}


int main()
{
	vector<int> v = { 55, 30, 15, 100, 1, 5, 70, 120 };

	QuickSort(v, 0, v.size() - 1);

	return 0;
}