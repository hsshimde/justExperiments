#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
//void BFS(const string& begin, const string& target, const vector<string>& words, vector<bool>& visited, size_t wordIndex, size_t& phase);

size_t getSameLetterCount(const string& s1, const string& s2);

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    size_t letterCount{ target.size() };
    queue<pair<string, int>> stateQueue;
    vector<bool> visited(words.size(), false);

    stateQueue.push(make_pair(begin, 0));

    
    bool bFoundPath{ false };
    while (!stateQueue.empty())
    {
        pair<string, int> currentState{ stateQueue.front() };
        stateQueue.pop();
        
 
        for (size_t i{}; i < words.size(); ++i)
        {
            if (!visited[i] && getSameLetterCount(currentState.first, words[i]) >= letterCount - 1)
            {
                visited[i] = true;

                if (words[i] == target)
                {
                    answer = currentState.second + 1;
                    bFoundPath = true;
                    break;
                }

                else
                {
                    stateQueue.push(make_pair(words[i], currentState.second + 1));
                }
            }
        }

        if (bFoundPath)
        {
            break;
        }

    }
    return answer;
}

size_t getSameLetterCount(const string& s1, const string& s2)
{
    size_t sameLetterCount{};

    for (size_t i{}; i < s1.size(); ++i)
    {
        if (s1[i] == s2[i])
        {
            sameLetterCount++;
        }
    }

    return sameLetterCount;
}

//void BFS(const string& begin,const string& target, const vector<string>& words, vector<bool>& visited, size_t wordIndex, size_t& phase)
//{
//
//}

//int main()
//{
//    string begin{ "hit" }, target{ "cog" };
//    vector<string> words{ "hot","dot","dog","lot","log","cog" };
//
//    int answer = solution(begin, target, words);
//
//    printf("%d", answer);
//
//    return 0;
//}