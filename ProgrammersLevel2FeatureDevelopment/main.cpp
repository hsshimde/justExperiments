#include <string>
#include <vector>

using namespace std;


vector<int> solution(vector<int> progresses, vector<int> speeds) 
{
    vector<int> answer;

    size_t workIndex{ 0 };
    size_t workSize{ progresses.size() };

    while (workIndex < workSize)
    {
        size_t lastWorkIndex{ workIndex };

        for (size_t i{workIndex}; i < workSize; i++)
        {
            progresses[i] += speeds[i];
        }
       
        while (workIndex < workSize && progresses[workIndex] >= 100)
        {
            workIndex++;
        }
       
        size_t workDoneCount{ workIndex - lastWorkIndex };

        if (workDoneCount > 0)
        {
            answer.emplace_back(workDoneCount);
        }

        
    }
    return answer;
}

int main()
{

}