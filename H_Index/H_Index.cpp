#include <string>
#include <vector>

using namespace std;

int solution(vector<int> citations) {

	int answer = 0;
	int highestPossibleIndex{ static_cast<int>(citations.size()) };
	for (; highestPossibleIndex > 0; highestPossibleIndex--)
	{
		int IndexCount{};
		for (size_t i{}; i < citations.size(); i++)
		{
			if (citations[i] >= highestPossibleIndex)
			{
				IndexCount++;
			}
		}

		if (IndexCount >= highestPossibleIndex)
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

int main()
{

}