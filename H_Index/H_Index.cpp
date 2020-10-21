#include <string>
#include <vector>

using namespace std;

int solution(vector<int> citations);

int main()
{

}

int solution(vector<int> citations) {

	int answer = 0;
	for (int highestPossibleIndex{ static_cast<int>(citations.size()) }; highestPossibleIndex > 0; highestPossibleIndex--)
	{
		int indexCount{};

		for (size_t i{}; i < citations.size(); i++)
		{
			if (citations[i] >= highestPossibleIndex)
			{
				indexCount++;
			}
		}

		if (indexCount >= highestPossibleIndex)
		{
			break;
		}
		else
		{
			continue;
		}

	}
	answer = highestPossibleIndex;

	return answer;
}