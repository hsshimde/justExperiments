#include <iostream>
#include <vector>	
#include <chrono>
#include <thread>
#include <memory>

const size_t MAX_COUNT = 15000;
const size_t THREAD_COUNT = 4;

bool IsPrimeNumber(size_t number, const std::vector<size_t>& primes)
{
	if (number == 2 || number == 3)
	{
		return true;
	}
	for (auto& i : primes)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

void Prsize_tPrimeNumbers(const std::vector<size_t>& primes)
{
	for (auto& i : primes)
	{
		std::cout << i << std::endl;
	}
}
size_t main()
{
	size_t num = 1;
	std::vector<size_t> primes;

	auto t0 = std::chrono::system_clock::now();
	std::vector<std::shared_ptr<std::thread>> threads;
	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		std::shared_ptr<std::thread> thread(new std::thread([&]()
			{
				while (true)
				{
					size_t n;
					n = num;
					num++;
					if (n >= MAX_COUNT)
					{
						break;
					}
					if (IsPrimeNumber(n, primes))
					{
						primes.push_back(n);
					}
				}
			}));
		threads.push_back(thread);
	}

	for (auto thread : threads)
	{
		thread->join();
	}
	auto t1 = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
	std::cout << "Took " << duration << " milliseconds." << std::endl;
	return 0;
}