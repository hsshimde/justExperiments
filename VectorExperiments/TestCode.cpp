#include <cassert>
#include <iostream>

#include "VectorExperiments.h"

int main()
{
	std::vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(4);
	v.push_back(12);
	v.push_back(7);
	v.push_back(11);

	int sum = vectorExperiments::Sum(v);
	int max = vectorExperiments::Max(v);
	int min = vectorExperiments::Min(v);
	float average = vectorExperiments::Average(v);
	int numWithMaxOccurence = vectorExperiments::NumberWithMaxOccurrence(v);
	vectorExperiments::SortDescending(v);

	assert(sum == 22);
	assert(max == 12);
	assert(min == 3);
	assert(average == 6.83333349f);
	assert(numWithMaxOccurence == 4);

	//for (auto& ptr : v)
	//{
	//	ptr = ptr + 20;
	//}

	for (int i = 0; i < (int)v.size() - 1; ++i)
	{
		assert(v[i] >= v[i + 1]);
	}

	return 0;
}