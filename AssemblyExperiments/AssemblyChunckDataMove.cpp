#include <stdio.h>
#include <Windows.h>


int main()
{
	const char* stringSource = "12345678";
	char stringDestination[9];

	stringDestination[8] = 0;

	__asm
	{
		lea esi, dword ptr[stringSource]
		lea edi, dword ptr[stringDestination]

		mov ecx, 9
		movsb
	}

-	printf("%s\n", stringDestination);

	return 0;
}