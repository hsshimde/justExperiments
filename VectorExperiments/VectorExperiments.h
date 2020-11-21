#pragma once

#include <vector>
#include <unordered_map>

namespace vectorExperiments
{
	int Sum(const std::vector<int>& v);
	int Min(const std::vector<int>& v);
	int Max(const std::vector<int>& v);
	float Average(const std::vector<int>& v);
	int NumberWithMaxOccurrence(const std::vector<int>& v);
	void SortDescending(std::vector<int>& v);
}