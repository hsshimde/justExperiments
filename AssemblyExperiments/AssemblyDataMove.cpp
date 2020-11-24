#include <Windows.h>
#include <stdio.h>
#include <conio.h>


int main()
{
	const char stringSource[] = "12345678";
	char stringDestination[9];

	stringDestination[8] = 0;

	__asm
	{
		lea esi, dword ptr[stringSource];
		lea edi, dword ptr[stringDestination];

			mov al, byte ptr[esi]
			mov byte ptr[edi], al

			mov al, byte ptr[esi + 1]
			mov byte ptr[edi+1], al

			mov al, byte ptr[esi + 2]
			mov byte ptr[edi + 2], al

			mov al, byte ptr[esi + 3]
			mov byte ptr[edi + 3], al

			mov al, byte ptr[esi + 4]
			mov byte ptr[edi + 4], al


			mov al, byte ptr[esi + 5]
			mov byte ptr[edi + 5], al

			mov al, byte ptr[esi + 6]
			mov byte ptr[edi + 6], al

			mov al, byte ptr[esi + 7]
			mov byte ptr[edi + 7], al

	}


	printf("%s\n", stringDestination);

	return 0;




}