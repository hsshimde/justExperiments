#include <string>
#include <vector>
#include <iostream>
using namespace std;

std::vector<int> fibonacci{};

int fib(int n)
{
    if (n == 0)
    {
        return fibonacci[n] = 0;
    }
    else if (n == 1)
    {
        return fibonacci[n] = 1;
    }
    
    else
    {
        if (fibonacci[n])
        {
            return fibonacci[n];
        }

        else
        {
            return fibonacci[n] = (fib(n - 1) + fib(n - 2)) % 1234567;
        }
    }

}

int solution(int n) {

    int answer{};

    fibonacci.resize(n + 1);

    answer = fib(n);
    
    return answer;
}