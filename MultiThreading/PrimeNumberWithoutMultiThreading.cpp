//#include <iostream>
//#include <vector>	
//#include <chrono>
//#include <thread>
//#include <memory>
//#include <mutex>
//
//const size_t MAX_COUNT = 1500000;
//const size_t THREAD_COUNT = 4;
//
//bool IsPrimeNumber(size_t number, const std::vector<size_t>& primes)
//{
//	if (number == 1)
//	{
//		return false;
//	}
//	else if (number == 2 || number == 3)
//	{
//		return true;
//	}
//	else
//	{
//		for (auto& i : primes)
//		{
//			if (number % i == 0)
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//void Prsize_tPrimeNumbers(const std::vector<size_t>& primes)
//{
//	for (auto& i : primes)
//	{
//		std::cout << i << std::endl;
//	}
//}
//size_t main()
//{
//	auto t0 = std::chrono::system_clock::now();
//	int number = 2;
//	std::vector<size_t> primes;
//	while (number < MAX_COUNT)
//	{
//		if (IsPrimeNumber(number, primes))
//		{
//			primes.push_back(number);
//		}
//		number++;
//	}
//	auto t1 = std::chrono::system_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
//	std::cout << "Took " << duration << " milliseconds.\n";
//	return 0;
//}