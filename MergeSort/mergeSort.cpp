#include <iostream>

using Data = int;
static constexpr size_t Size{ 100 };
Data buffer[Size];
void mergeSort(Data arr[], int begin, int end);
void bubbleSort(Data arr[], int begin, int end);

int main()
{
	Data arr[Size];

	for (int i{ }; i < Size; i++)
	{
		arr[i] = 80 - i;
	}

	mergeSort(arr, 0, Size - 1);

	for (int i{}; i < Size; ++i)
	{
		printf("%d\n", arr[i]);
	}

	return 0;
}

void mergeSort(Data myArray[], int begin, int end)
{
	if (end - begin <= 10)
	{
		return bubbleSort(myArray, begin, end);
	}

	int half{ (begin + end) / 2 };


	mergeSort(myArray, begin, half);

	mergeSort(myArray, half + 1, end);


	int mergeIndex{ begin };
	int formerArrayIndex{ begin };
	int latterArrayIndex{ half + 1 };

	for (int i{ begin }; i <= end; ++i)
	{
		buffer[i] = myArray[i];
	}

	while (formerArrayIndex <= half && latterArrayIndex <= end)
	{
		Data smaller{ (buffer[formerArrayIndex] < buffer[latterArrayIndex]) ? buffer[formerArrayIndex++] : buffer[latterArrayIndex++] };

		myArray[mergeIndex++] = smaller;
	}

	while (formerArrayIndex <= half)
	{
		myArray[mergeIndex++] = buffer[formerArrayIndex++];
	}


	while (latterArrayIndex <= end)
	{
		myArray[mergeIndex++] = buffer[latterArrayIndex++];
	}

	return;

}

void bubbleSort(Data myArray[], int begin, int end)
{
	int size{ end - begin + 1 };
	int temp{};

	for (int i{}; i < size; ++i)
	{
		for (int j{ end }; j > i; --j)
		{
			if (myArray[j - 1] > myArray[j])
			{
				temp = myArray[j];
				myArray[j] = myArray[j - 1];
				myArray[j - 1] = temp;
			}
		}
	}


}