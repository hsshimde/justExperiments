#include <iostream>
#include <cstdio>
#include <iomanip>

void printPyramidUpsideDown(size_t lineNumber);
void printPyramid(size_t lineNumber);
int main()
{
	while (true)
	{

		std::cout << "Insert the numer of line : ";
		size_t lineNumber{};
		std::cin >> lineNumber;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Invalid Input ! Ending the program.\n";
			break;
		}
		printPyramidUpsideDown(lineNumber);
		printPyramid(lineNumber);

	}
	return 0;

}

void printPyramidUpsideDown(size_t lineNumber)
{
	size_t width{ 2 * lineNumber - 1 };
	for (size_t i{}; i < lineNumber; i++)
	{

		for (size_t k{}; k < i; k++)
		{
			printf(" ");
		}

		for (size_t k{}; k < width - 2 * i; k++)
		{
			printf("*");
		}

		for (size_t k{}; k < i; k++)
		{
			printf(" ");
		}
		printf("\n");
	}
}

void printPyramid(size_t lineNumber)
{
	size_t width{ 2 * lineNumber - 1 };

	for (size_t i{1}; i <= lineNumber;++i)
	{
		size_t spaceCount{(width-(2*i-1))/2};

		for (size_t j{}; j < spaceCount; ++j)
		{
			printf(" ");
		}
		
		for (size_t j{}; j < 2 * i - 1; j++)
		{
			printf("*");
		}

		for (size_t j{}; j < spaceCount; ++j)
		{
			printf(" ");
		}

		printf("\n");
	}
}