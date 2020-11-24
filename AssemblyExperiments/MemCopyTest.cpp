#include <Windows.h>
#include <stdio.h>	
#include <conio.h>

void memcpy_test(void* pDestination, void* pSource, DWORD dwSize)
{
	__asm
	{
		mov esi, dword ptr[pSource]
		mov edi, dword ptr[pDestination]

		mov ecx, dword ptr[dwSize]

		test ecx, 1

	}
}