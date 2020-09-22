#include <iostream>
#include <string>

const int ArSize = 10;
const int MaxLen = 81;


int main()
{
	using std::string;

	string name{};
	std::cout << "Hello ~ what is your name sir ? : ";
	std::getline(std::cin,name);

	std::cout << name << ", Please insert " << ArSize << " sayings (Press \"Enter\" to end : )\n";

	string sayings[MaxLen];

	char tmp[MaxLen];

	size_t i{};
	for (; i < ArSize; i++)
	{
		std::cout << i + 1 << ": ";
		std::cin.get(tmp, MaxLen);
		std::cin.get();

		
			if (tmp[0] == '\0')
			{
				std::cout << "Reached to break point !\n";
				break;
			}
		
			sayings[i] = tmp;
	}

	size_t total{ i };

	if (total > 0)
	{
		std::cout << "============You have inserted following idioms==========\n";
		for (size_t i{}; i < total; i++)
		{
			std::cout << sayings[i] << std::endl;
		}
		
	}

	string* shortest = &sayings[0];
	string* first = &sayings[0];

	for (i = 1 ; i < total; i++)
	{
		if (sayings[i].size() < shortest->size())
		{
			shortest = &sayings[i];
		}

		if (sayings[i] < *first)
		{
			first = &sayings[i];
		}
	}
	
	std::cout << "The shortest idiom : " << *shortest << std::endl;
	std::cout << "The first idiom in a dictionary : " << *first << std::endl;



	return 0;
}