#include <string>
#include <vector>

using namespace std;

void DFS(int n, vector<vector<int>>&computers, vector<bool>& visited);

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;


    vector<bool>visited(n, false);

    for (size_t i{}; i < n; ++i)
    {
        if (visited[i] == false)
        {
            visited[i] = true;
            answer++;
            DFS(i, computers, visited);
        }
    }

    return answer;
}

void DFS(int n,vector<vector<int>>& computers ,vector<bool>& visited)
{
    size_t computerNumber{ visited.size() };

    for (size_t i{}; i < computerNumber; i++)
    {
        if (i != n && visited[i] == false && computers[n][i])
        {
            visited[i] = true;
            DFS(i, computers, visited);
        }
    }
    return;
    
}
//
//int main()
//{
//
//}