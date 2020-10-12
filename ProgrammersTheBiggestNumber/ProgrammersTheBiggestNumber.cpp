#include <string>
#include <vector>
#include <algorithm>

#include "MyNumberString.h"

using namespace std;

string solution(vector<int> numbers) {
    string answer = "";
    vector<MyNumberString>numberString(numbers.size());

    for (size_t i{}; i < numbers.size(); ++i)
    {
        numberString.emplace_back(MyNumberString{numbers[i]});
    }

    sort(begin(numberString), end(numberString),std::greater<MyNumberString>());

    for (const MyNumberString& numberStr : numberString)
    {
        answer += numberStr.GetNumber();
    }


    return answer;
}

int main()
{

}