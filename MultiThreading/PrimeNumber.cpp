#include <iostream>
#include <vector>	
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>

const size_t MAX_COUNT = 15000000;
const size_t THREAD_COUNT = 4;/*
std::vector<std::shared_ptr<std::thread>> threads;*/
bool IsPrimeNumber(size_t number)
{
	if (number == 1)
	{
		return false;
	}
	else if (number == 2 || number == 3)
	{
		return true;
	}
	else
	{
		for (size_t i = 2; i < number; i++)
		{
			if (number % 2 == 0)
			{
				return false;
			}
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
	int num = 1;
	std::recursive_mutex numMutex;
	std::vector<size_t> primes;
	std::recursive_mutex primesMutex;

	auto t0 = std::chrono::system_clock::now();
	std::vector<std::shared_ptr<std::thread>> threads;
	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		std::shared_ptr<std::thread> thread(new std::thread([&]()
			{
				while (true)
				{
					int n;
					{
						std::lock_guard<std::recursive_mutex> numLock(numMutex);
						n = num;
						num++;
					}
					if (n >= MAX_COUNT)
					{
						break;
					}
					if (IsPrimeNumber(n))
					{
						std::lock_guard<std::recursive_mutex> primesLock(primesMutex);
						primes.push_back(n);
					}
				}
			}));
		threads.push_back(thread);
	}
	for (auto& thread : threads)
	{
		thread->join();
	}
	auto t1 = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
	std::cout << "Took " << duration << " milliseconds.\n";
	return 0;
}