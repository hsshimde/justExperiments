#include <stdio.h>

int main()
{
	int iClockLow;
	int iElapsedClock;

	__asm
	{
		rdtsc
		mov dword ptr[iClockLow], eax

	}

	//GetTickCount();

	__asm
	{
		rdtsc
		sub eax, dword ptr[iClockLow]
		mov dword ptr[iElapsedClock], eax
	}

	printf("%u\n", iElapsedClock);
	return 0;
}