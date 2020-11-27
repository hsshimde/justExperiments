#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SpecQueue
{
public:
    SpecQueue() :numbers{} {}

    void DoOperation(const string& op)
    {
        switch (op[0])
        {
        case 'I':
        {
            string number{};

            for (size_t i{ 2 }; i < op.size(); ++i)
            {
                number.push_back(op[i]);
            }

            numbers.push_back(stoi(number));
            break;
        }

        case 'D':
        {
            if (op[2] == '-')
            {
                if (numbers.empty())
                {
                    return;
                }

                auto iter = min_element(begin(numbers), end(numbers));
                numbers.erase(iter);

            }

            else
            {
                if (numbers.empty())
                {
                    return;
                }

                auto iter = max_element(begin(numbers), end(numbers));
                numbers.erase(iter);

            }

            break;
        }


        }

        return;
    }

    bool IsEmpty() const { return numbers.empty(); }


    int GetMax() const
    {
        auto Max = max_element(begin(numbers), end(numbers));

        return *Max;
    }

    int GetMin() const
    {
        auto Min = min_element(begin(numbers), end(numbers));

        return *Min;
    }

private:
    vector<int> numbers;

};

vector<int> solution(vector<string> operations) {
    vector<int> answer;

    SpecQueue q{};

    for (const auto& i : operations)
    {
        q.DoOperation(i);
    }

    if (q.IsEmpty())
    {
        answer.push_back(0);
        answer.push_back(0);
    }

    else
    {
        answer.push_back(q.GetMax());
        answer.push_back(q.GetMin());
    }



    return answer;
}

