#include "VectorExperiments.h"

static void QuickSortDescendingRecursive(std::vector<int>& v, int left, int right);
static void BubbleSortDescending(std::vector<int>& v);

namespace vectorExperiments
{
	int Sum(const std::vector<int>& v)
	{
		size_t vectorSize{ v.size() };

		int sum{};

		for (size_t i{}; i < vectorSize; i++)
		{
			sum += v[i];
		}

		return sum;

	}

	int Min(const std::vector<int>& v)
	{
		size_t vectorSize{ v.size() };

		int min{ INT32_MAX };

		for (size_t i{ 0 }; i < vectorSize; ++i)
		{
			if (v[i] < min)
			{
				min = v[i];
			}
		}

		return min;
	}

	int Max(const std::vector<int>& v)
	{
		size_t vectorSize{ v.size() };

		int max{ INT32_MIN };

		for (size_t i{ 0 }; i < vectorSize; ++i)
		{
			if (v[i] > max)
			{
				max = v[i];
			}
		}

		return max;
	}

	float Average(const std::vector<int>& v)
	{
		if (v.size() == 0)
		{
			return 0.0;
		}

		return (static_cast<float>(Sum(v)) / v.size());
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		size_t vectorSize{ v.size() };

		if (vectorSize == 0)
		{
			return 0;
		}

		std::unordered_map<int, size_t> elementCountMap{};

		for (size_t i{}; i < vectorSize; ++i)
		{
			elementCountMap[v[i]]++;
		}

		size_t maxCount{};
		size_t maxOccurenceNumberIndex{};

		for (size_t i{ 0 }; i < vectorSize; ++i)
		{
			if (elementCountMap[v[i]] > maxCount)
			{
				maxOccurenceNumberIndex = i;
				maxCount = elementCountMap[v[i]];
			}
		}

		return v[maxOccurenceNumberIndex];

	}

	void SortDescending(std::vector<int>& v)
	{
		size_t vectorSize{ v.size() };

		if (vectorSize == 0 || vectorSize == 1)
		{
			return;
		}

		else if (vectorSize < 10)
		{
			BubbleSortDescending(v);
		}

		else
		{
			QuickSortDescendingRecursive(v, 0, static_cast<int>(vectorSize - 1));
		}
	}

}

void QuickSortDescendingRecursive(std::vector<int>& v, int begin, int end)
{
	//Bug occured when the input begin and end were typed as "size_t" 
	///probably because when 'begin' reached 0, its value go all the way back to INT32_MAX //-> vector range violation occured

	int left{ begin };
	int right{ end };
	int pivot{ v[(right + left) / 2] };

	while (left < right)
	{

		while (v[right] < pivot)
		{
			right--;
		}

		while (v[left] > pivot)
		{
			left++;
		}

		if (right >= left)
		{
			int temp{ v[right] };
			v[right--] = v[left];
			v[left++] = temp;
		}

	}


	if (right > begin)
	{
		QuickSortDescendingRecursive(v, begin, right);
	}


	if (left < end)
	{
		QuickSortDescendingRecursive(v, left, end);
	}

}



void BubbleSortDescending(std::vector<int>& v)
{
	size_t vectorSize{ v.size() };

	for (size_t i{}; i < vectorSize; i++)
	{
		for (size_t j{ vectorSize - 1 }; j > i; j--)
		{
			if (v[j] > v[j - 1])
			{
				int temp{ v[j] };
				v[j] = v[j - 1];
				v[j - 1] = temp;
			}
		}
	}
}