#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


//int main()
//{
//    vector<vector<string>> clothes{};
//    auto answer = solution(clothes);
//
//    
//}
int solution(vector<vector<string>> clothes) {
    int answer = 0;

    unordered_map<string, size_t> ownClothesCountMap;

    for (size_t i{}; i < clothes.size(); ++i)
    {
        ownClothesCountMap[clothes[i][1]]++;
    }

    size_t wholeCount{1};

    for (const auto& i : ownClothesCountMap)
    {
        wholeCount *= (i.second+1);
    }

    wholeCount--;


    answer = static_cast<int>(wholeCount);

    return answer;
}