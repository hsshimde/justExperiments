#include <string>
#include <vector>

using namespace std;

int solution(string skill, vector<string> skill_trees)
{
	int answer = 0;

	size_t skillSize{ skill.size() };


	for (size_t i{}; i < skill_trees.size(); ++i)
	{
		size_t currentCheckIndex{};
		bool bProperSkillTree{ true };

		for (size_t j{}; j < skill_trees[i].size(); ++j)
		{
			

			for (size_t k{}; k < skillSize; ++k)
			{
				if (skill_trees[i][j] == skill[k])
				{
					if (k == currentCheckIndex)
					{
						currentCheckIndex++;
					}
					
					else
					{
						bProperSkillTree = false;
						break;
					}
				}
			}

			if (!bProperSkillTree)
			{
				break;
			}

		}

		if (bProperSkillTree)
		{
			answer++;
		}
		
	}

	return answer;
}/*
int main()
{

}*/