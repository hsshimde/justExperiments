#include <string>
#include <vector>

using namespace std;

void DFS(vector<vector<int>>& link, vector<bool>& visited,size_t nodeNumber);
int solution(int n, vector<vector<int>> computers) {
    int answer = 0;

    vector<bool> visited(n, false);

    for (size_t i{}; i < computers.size(); ++i)
    {
        if (!visited[i])
        {
            answer++;
            DFS(computers, visited, i);
        }
    }

    return answer;
}

void DFS(vector<vector<int>>& link, vector<bool>& visited, size_t nodeNumber)
{
    visited[nodeNumber] = true;
    for (size_t i{}; i < visited.size(); ++i)
    {
        if (link[nodeNumber][i] && !visited[i])
        {
            DFS(link, visited, i);
        }
    }
}
